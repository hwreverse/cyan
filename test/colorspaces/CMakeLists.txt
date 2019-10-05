include_directories ( ${TEST_SOURCE_DIR}/src )

add_executable ( rgb2hsv rgb2hsv.c)
target_link_libraries ( rgb2hsv cyan )
add_test (NAME test_rgb2hsv COMMAND rgb2hsv )

add_executable ( hsv2rgb hsv2rgb.c)
target_link_libraries ( hsv2rgb cyan )
add_test (NAME test_hsv2rgb COMMAND hsv2rgb )
