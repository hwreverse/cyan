# CMake generated Testfile for 
# Source directory: /home/sf/Prog/cyan/test/color
# Build directory: /home/sf/Prog/cyan/test/color
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(rgb_to_xyz "sh" "-c" "/home/sf/Prog/cyan/test/color/rgb_to_xyz  > ./rgb_to_xyz.out")
add_test(COMPARE_rgb_to_xyz "/usr/bin/cmake" "-E" "compare_files" "./rgb_to_xyz.out" "/home/sf/Prog/cyan/test/reference_output/rgb_to_xyz.output")
add_test(refwhite_get_xyz "sh" "-c" "/home/sf/Prog/cyan/test/color/refwhite_get_xyz  > ./refwhite_get_xyz.out")
add_test(COMPARE_refwhite_get_xyz "/usr/bin/cmake" "-E" "compare_files" "./refwhite_get_xyz.out" "/home/sf/Prog/cyan/test/reference_output/refwhite_get_xyz.output")
