add_executable ( print_all_markers print_all_markers.c)
target_link_libraries ( print_all_markers cyan )

add_test (NAME printallmarkers COMMAND print_all_markers output.ppm)

