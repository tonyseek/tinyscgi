cmake_minimum_required (VERSION 2.8)
project (tinyscgi)

# use custom cmake modules
set (CMAKE_MODULE_PATH
     ${CMAKE_MODULE_PATH}
     ${CMAKE_SOURCE_DIR}/cmake/modules/)

add_subdirectory (src)
add_subdirectory (tests)
