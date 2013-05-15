#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <uv.h>
#include "tscgi/buffer.h"
#include "tscgi/header.h"
#include "tscgi/request.h"
#include "tscgisrv/server.h"

lua_State *L;

static void init_scgi_server(struct scgi_server *);

int main(int argc, char **argv)
{
    int error_code;
    struct scgi_server s;
    char *script_filename;

    /* check arguments */
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s LUA_SCRIPT", argv[0]);
        return EXIT_FAILURE;
    }
    else
    {
        script_filename = argv[1];
    }

    /* initialize Lua VM */
    L = luaL_newstate();
    luaL_openlibs(L);

    /* load Lua script */
    error_code = luaL_loadfile(L, script_filename) || lua_pcall(L, 0, 0, 0);
    if (error_code)
    {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return EXIT_FAILURE;
    }

    /* load "application" function */
    lua_getglobal(L, "application");
    if (!lua_isfunction(L, -1))
    {
        fprintf(stderr, "'application' must be function.\n");
        return EXIT_FAILURE;
    }

    /* startup service */
    init_scgi_server(&s);
    listen_scgi_server(s);

    lua_close(L);
    return EXIT_SUCCESS;
}

static void process_request(struct scgi_server *s, struct request *request,
                            struct buffer *response_buffer)
{
    struct header_list *header_ptr;
    char *response_bytes;
    const char *f_status, *f_cttype, *f_body;
    int error_occured = 0;

    header_ptr = request->headers;

    /* push function */
    if (!lua_isfunction(L, -1))
        lua_getglobal(L, "application");

    /* push arg[0]: request headers */
    lua_newtable(L);

    while ((header_ptr = header_ptr->next))
    {
        /* push table item */
        if (header_ptr->item.name)
        {
            lua_pushstring(L, header_ptr->item.value);
            lua_setfield(L, -2, header_ptr->item.name);
        }
    }

    /* call function (1 input args, 3 expect return values) */
    if (lua_pcall(L, 1, 3, 0) != 0)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, -1);
        error_occured = 1;
    }

    /* rv[2]: content-type */
    if (lua_isnil(L, -1))
        f_status = "text/plain";
    else if (lua_isstring(L, -1))
        f_status = lua_tostring(L, -1);
    else
    {
        fprintf(stderr, "third rv of 'application' must be string or nil\n");
        error_occured = 1;
    }

    /* rv[1]: status */
    if (lua_isnil(L, -2))
        f_status = "200 OK";
    else if (lua_isstring(L, -2))
        f_status = lua_tostring(L, -2);
    else
    {
        fprintf(stderr, "second rv of 'application' must be string or nil\n");
        error_occured = 1;
    }

    /* rv[0]: response body */
    if (lua_isstring(L, -3))
        f_body = lua_tostring(L, -3);
    else
    {
        fprintf(stderr, "first rv of 'application' must be string\n");
        error_occured = 1;
    }

    /* build response */
    response_bytes = malloc(sizeof(char) * 1024);
    memset(response_bytes, 0, sizeof(char) * 1024);
    if (error_occured)
    {
        strcpy(
            response_bytes,
            "Status: 500 Internal Server Error\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<h1>500 Internal Server Error</h1>"
        );

    }
    else
    {
        sprintf(
            response_bytes,
            "Status: %s\r\nContent-Type: %s\r\n\r\n%s",
            f_status, f_cttype, f_body
        );
    }

    /* send back response */
    buffer_init(response_buffer, response_bytes, strlen(response_bytes));
}

static void init_scgi_server(struct scgi_server *s)
{
    s->loop = uv_default_loop();
    s->max_conn = 128;
    s->process_request = &process_request;
    s->process_bad_request = NULL;

    s->bind_addrs[0] = uv_ip4_addr("0.0.0.0", 8000);
    s->nbind_addrs = 1;
}
