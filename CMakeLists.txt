### CMake file for cyan 
###
###     Author : glaconbleu@codices.org
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (cyan)
set (cyan_VERSION_MAJOR 0)
set (cyan_VERSION_MINOR 1)
set (cyan_VERSION_PATCH 1)
set (cyan_VERSION_STRING
	${cyan_VERSION_MAJOR}.${cyan_VERSION_MINOR}.${cyan_VERSION_PATCH} )

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )

# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
        set(var INSTALL_${p}_PATH)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()

### Options ###

option(ENABLE_tirpc "Use the tirpc library for file saving/loading" ON)

### Search for tirpc

if (ENABLE_tirpc)
    find_package(tirpc)
    if (LIBTIRPC_FOUND)
        set ( HAVE_TIRPC 1)
    else()
        set ( HAVE_TIRPC 0)
        message( FATAL_ERROR "Cannot find tirpc lib.")
    endif()
else()
    message("Not using tirpc lib. Load/save functions will not be available")
    set ( HAVE_TIRPC 0 )
endif()

### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		         "${PROJECT_SOURCE_DIR}/src/config.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
                      )

if (LIBNETPBM_FOUND)
    include_directories( "${LIBNETPBM_INCLUDE_DIR}" )
endif()

### File lists

file( GLOB src "src/*.c"  )
file( GLOB hdr "include/*.h"  )
file( GLOB hdr_algebra "include/algebra/*.h"  )
file( GLOB hdr_vision  "include/vision/*.h"  )
file( GLOB hdr_image   "include/image/*.h"  )
file( GLOB hdr_structs "include/structs/*.h"  )

### Targets

add_library( "cyan" SHARED ${src} ${hdr} ) 

set_target_properties(cyan PROPERTIES VERSION ${cyan_VERSION_STRING}
                                         SOVERSION ${cyan_VERSION_MAJOR})

### Linking

target_link_libraries( "cyan" "m" )
if (LIBNETPBM_FOUND)
    target_link_libraries( "cyan" ${LIBTIRPC_LIBRARY} )
endif()

### Cmake file

configure_file(cyanConfig.cmake.in "${PROJECT_BINARY_DIR}/cyanConfig.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyanConfig.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cyan" COMPONENT dev )  

configure_file(cyanConfigVersion.cmake.in
	"${PROJECT_BINARY_DIR}/cyanConfigVersion.cmake" @ONLY)

install ( FILES "${PROJECT_BINARY_DIR}/cyanConfigVersion.cmake" 
      DESTINATION "${INSTALL_LIB_PATH}/cyan" COMPONENT dev )  

### Install 

install( TARGETS "cyan"
	    RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
	    LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
            ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )

install( FILES ${hdr}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/${name}
	    COMPONENT main )
install( FILES ${hdr_algebra}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/algebra${name}
	    COMPONENT main )
install( FILES ${hdr_vision}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/vision/${name}
	    COMPONENT main )
install( FILES ${hdr_image}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/image/${name}
	    COMPONENT main )
install( FILES ${hdr_structs}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/structs/${name}
	    COMPONENT main )

# Regression tests

enable_testing()
add_subdirectory(test)

