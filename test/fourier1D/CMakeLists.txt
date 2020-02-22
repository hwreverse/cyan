add_executable ( fourier fourier1D.c)
target_link_libraries ( fourier cyan )

add_test (NAME fourier1D COMMAND fourier1D)

