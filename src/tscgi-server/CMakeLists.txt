# include headers
include_directories (.)

find_package (Libuv REQUIRED)

# add library target
add_library (tscgi-server server.c)
target_link_libraries (tscgi-server ${LIBUV_LIBRARIES} tscgi)

## install library target
install (TARGETS tscgi-server
         DESTINATION "lib")
install (FILES server.h
         DESTINATION "include/tscgi-server")
