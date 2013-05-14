find_package (Check REQUIRED)
include_directories (${CHECK_INCLUDE_DIRS})

# copy test data
configure_file (data/test_netstring_1.txt
                ${CMAKE_CURRENT_BINARY_DIR}/data/test_netstring_1.txt
                COPYONLY)

# compile test case
add_library (testtscgi test_buffer.c test_header.c test_netstring.c
             test_request.c)
target_link_libraries (testtscgi ${CHECK_LIBRARIES} tscgi)

# compile test driver
add_executable (check_tscgi check_tscgi.c)
target_link_libraries (check_tscgi ${CHECK_LIBRARIES} tscgi testtscgi)

# add compiled tests
add_test (NAME check_tscgi
          COMMAND ${CMAKE_CURRENT_BINARY_DIR}/check_tscgi
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
