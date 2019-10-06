add_executable ( rgb_to_xyz rgb_to_xyz.c)
target_link_libraries ( rgb_to_xyz cyan )

add_test(NAME rgb_to_xyz COMMAND sh -c "$<TARGET_FILE:rgb_to_xyz>  > ./rgb_to_xyz.out")

add_test(NAME COMPARE_rgb_to_xyz COMMAND ${CMAKE_COMMAND} -E compare_files
                ./rgb_to_xyz.out 
                ${PROJECT_SOURCE_DIR}/test/reference_output/rgb_to_xyz.output )
