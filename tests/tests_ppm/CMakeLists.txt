add_executable ( save_ppm save_ppm.c)
target_link_libraries ( save_ppm cyan )
add_test (NAME test_saveppm COMMAND saveppm )

