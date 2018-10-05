include_directories ( ${TEST_SOURCE_DIR}/src )

add_executable (test_lapacke main.c)
target_link_libraries (test_lapacke ${LAPACKE_LIBRARY} )

add_test (NAME test_simple COMMAND test_lapacke )
