add_executable ( save_ppm save_ppm.c)
target_link_libraries ( save_ppm cyan )

add_executable ( load_ppm load_ppm.c)
target_link_libraries ( load_ppm cyan )

###
### test 01 : Write a test file
###
#######################################################

add_test (NAME 01_saveppm COMMAND save_ppm 01_save_ppm.ppm)
add_test ( 01_saveppm_compare ${CMAKE_COMMAND} -E compare_files
    01_save_ppm.ppm
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_output/netpbm_${ENABLE_netpbm}/01_save_ppm.ppm)


###
### test 02 : Input : a P3 - 8bits color ppm file (lena)
###
#######################################################

add_test (NAME 02_loadppm_P38b COMMAND load_ppm 
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_input/lena_P3.ppm
    02_P38b.ppm)
add_test ( 02_loadppm_P38b_compare ${CMAKE_COMMAND} -E compare_files
    02_P38b.ppm
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_output/netpbm_${ENABLE_netpbm}/02_P38b.ppm)


###
### test 03 : Input : a P6 - 8bits color ppm file (lena)
###
#######################################################

add_test (NAME 03_loadppm_P68b COMMAND load_ppm 
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_input/lena_P6.ppm
    03_P68b.ppm)
add_test ( 03_loadppm_P68b_compare ${CMAKE_COMMAND} -E compare_files
    03_P68b.ppm
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_output/netpbm_${ENABLE_netpbm}/03_P68b.ppm)


###
### test 04 : Input : a P3 - 16bits color ppm file 
###
#######################################################

add_test (NAME 04_loadppm_P316b COMMAND load_ppm 
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_input/DeltaE_16bit_gamma2.2_P3_16bit.ppm
    04_P316b.ppm)
add_test ( 04_loadppm_P316b_compare ${CMAKE_COMMAND} -E compare_files
    04_P316b.ppm
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_output/netpbm_${ENABLE_netpbm}/04_P316b.ppm)


###
### test 05 : Input : a P6 - 16bits color ppm file 
###
#######################################################

add_test (NAME 05_loadppm_P616b COMMAND load_ppm 
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_input/DeltaE_16bit_gamma2.2_P6_16bit.ppm
    05_P616b.ppm)
add_test ( 05_loadppm_P616b_compare ${CMAKE_COMMAND} -E compare_files
    05_P616b.ppm
    ${CMAKE_SOURCE_DIR}/tests/ppm_files/ref_output/netpbm_${ENABLE_netpbm}/05_P616b.ppm)

