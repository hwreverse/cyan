include_directories ( ${TEST_SOURCE_DIR}/src )

add_executable (test_01 main.c)

target_link_libraries (test_01 malib )

add_test (NAME test_simple COMMAND test_01 )
