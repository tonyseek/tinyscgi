cmake_minimum_required (VERSION 2.8)
project (tinyscgi)

# use testing
enable_testing ()

# use custom cmake modules
set (CMAKE_MODULE_PATH
     ${CMAKE_MODULE_PATH}
     ${CMAKE_SOURCE_DIR}/cmake/modules/)

# add source and testing
add_subdirectory (src)
add_subdirectory (tests)
