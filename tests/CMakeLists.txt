enable_testing ()

find_package (Check REQUIRED)
include_directories (${CHECK_INCLUDE_DIRS})

add_library (testtscgi test_header.c test_netstring.c test_request.c)

add_executable (check_tscgi check_tscgi.c)
target_link_libraries (check_tscgi ${CHECK_LIBRARIES} tscgi testtscgi)

add_test (check_tscgi ${CMAKE_CURRENT_BINARY_DIR}/check_tscgi)
