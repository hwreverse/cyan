add_executable ( rgb_to_xyz rgb_to_xyz.c)
target_link_libraries ( rgb_to_xyz cyan )

add_test(NAME rgb_to_xyz 
         COMMAND sh -c "$<TARGET_FILE:rgb_to_xyz>  > ./rgb_to_xyz.out")

add_test(NAME COMPARE_rgb_to_xyz COMMAND ${CMAKE_COMMAND} -E compare_files
            ./rgb_to_xyz.out 
            ${PROJECT_SOURCE_DIR}/test/reference_output/rgb_to_xyz.output )

##############################################################################

add_executable ( refwhite_get_xyz refwhite_get_xyz.c)
target_link_libraries ( refwhite_get_xyz cyan )

add_test(NAME refwhite_get_xyz 
         COMMAND sh -c "$<TARGET_FILE:refwhite_get_xyz>  > ./refwhite_get_xyz.out")

add_test(NAME COMPARE_refwhite_get_xyz COMMAND ${CMAKE_COMMAND} -E compare_files
            ./refwhite_get_xyz.out 
            ${PROJECT_SOURCE_DIR}/test/reference_output/refwhite_get_xyz.output )
