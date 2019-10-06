add_executable ( image image.c)
target_link_libraries ( image cyan )

add_test (NAME image COMMAND image)

