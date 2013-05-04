cmake_minimum_required (VERSION 2.8)
project (tinyscgi)

include_directories (src/scgi)

add_library (tscgi
             src/scgi/header.c
             src/scgi/netstring.c
             src/scgi/request.c)

add_executable (tinyscgi src/tinyscgi.c)
target_link_libraries (tinyscgi tscgi)
