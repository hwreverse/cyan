add_executable ( test1D test1D.c)
target_link_libraries ( test1D cyan )

add_test (NAME test1D COMMAND test1D)

