cmake_minimum_required (VERSION 2.8)
project (tinyscgi)

set (LIBTSCGI_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/tscgi")

# libtscgi targets
include_directories ("${LIBTSCGI_SOURCE_DIR}")
add_library (tscgi
             "${LIBTSCGI_SOURCE_DIR}/header.c"
             "${LIBTSCGI_SOURCE_DIR}/netstring.c"
             "${LIBTSCGI_SOURCE_DIR}/request.c")

# server command tool targets
add_executable (tinyscgi "${PROJECT_SOURCE_DIR}/src/tinyscgi.c")
target_link_libraries (tinyscgi tscgi)

# install targets
install (TARGETS tinyscgi
         DESTINATION "bin")
install (TARGETS tscgi
         DESTINATION "lib")
install (FILES
         ${LIBTSCGI_SOURCE_DIR}/errors.h
         ${LIBTSCGI_SOURCE_DIR}/header.h
         ${LIBTSCGI_SOURCE_DIR}/netstring.h
         ${LIBTSCGI_SOURCE_DIR}/request.h
         DESTINATION "include/tscgi")
