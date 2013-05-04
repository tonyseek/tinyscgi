cmake_minimum_required (VERSION 2.8)
project (tinyscgi)

# libtscgi
include_directories (src/tscgi)
add_library (tscgi
             src/tscgi/header.c
             src/tscgi/netstring.c
             src/tscgi/request.c)

# scgi server
add_executable (tinyscgi src/tinyscgi.c)
target_link_libraries (tinyscgi tscgi)
