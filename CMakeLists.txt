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

option(ENABLE_TIRPC   "Use the tirpc library for file saving/loading" ON)
option(ENABLE_GETTEXT "Use the gettext library for int18n" ON)

option(BUILD_TOOLS  "Build and install cyan tools" ON)
option(BUILD_TEST   "Build cyan tests" OFF)

option(CFG_VERBOSE_ERRORS   "Error output on stderr" ON)

### Cyan options processing

if (CFG_VERBOSE_ERRORS)
    set ( CYAN_CFG_VERBOSE_ERRORS 1)
else()
    set ( CYAN_CFG_VERBOSE_ERRORS 0)
endif()

### Search for tirpc

if (ENABLE_TIRPC)
    find_package(tirpc)
    if (LIBTIRPC_FOUND)
        set ( HAVE_LIBTIRPC 1)
    else()
        set ( HAVE_LIBTIRPC 0)
        message( FATAL_ERROR "Cannot find tirpc lib.")
    endif()
else()
    message("Not using tirpc lib. Load/save functions will not be available")
    set ( HAVE_TIRPC 0 )
endif()


### Search for gettext

if (ENABLE_GETTEXT)
    find_package(Gettext)
    if (GETTEXT_FOUND)
        set ( HAVE_GETTEXT 1)
    else()
        set ( HAVE_GETTEXT 0)
        message( FATAL_ERROR "Cannot find gettext lib.")
    endif()
else()
    message("Not using gettext. Messages will be displayed in english only")
    set ( HAVE_GETTEXT 0 )
endif()

### Config File

configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in"
		         "${PROJECT_SOURCE_DIR}/include/cyan/common/config.h" )

### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	                 "${CMAKE_CURRENT_BINARY_DIR}" 
                      )

if (LIBNETPBM_FOUND)
    include_directories( "${LIBNETPBM_INCLUDE_DIR}" )
endif()

### File lists

file( GLOB src  "src/*.c"  
                "src/color/*.c"
                "src/common/*.c" )

file( GLOB hdr         "include/cyan/*.h"  )
file( GLOB hdr_image   "include/cyan/image/*.h"  )
file( GLOB hdr_color   "include/cyan/color/*.h"  )
file( GLOB hdr_vision  "include/cyan/vision/*.h"  )
file( GLOB hdr_3dmodel "include/cyan/3dmodel/*.h"  )
file( GLOB hdr_common  "include/cyan/common/*.h"  )

### Targets

add_library( "cyan" SHARED ${src} ) 

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

install( FILES ${hdr_image}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/image/${name}
	    COMPONENT main )

install( FILES ${hdr_color}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/color/${name}
	    COMPONENT main )

install( FILES ${hdr_vision}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/vision/${name}
	    COMPONENT main )

install( FILES ${hdr_3dmodel}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/3dmodel/${name}
	    COMPONENT main )

install( FILES ${hdr_common}
	    DESTINATION ${INSTALL_HEADERS_PATH}/cyan/common/${name}
	    COMPONENT main )

# Build Tools

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif()

# Regression tests

if (BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

# Int18n

if (ENABLE_GETTEXT)
    add_subdirectory(po)
endif()

### Pretty Display :

MESSAGE(STATUS "*********************************************************")
MESSAGE(STATUS "")
MESSAGE(STATUS "Build type:        " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "")
MESSAGE(STATUS "ENABLE_TIRPC:      " ${ENABLE_TIRPC})
MESSAGE(STATUS "ENABLE_GETTTEXT:   " ${ENABLE_GETTEXT})
MESSAGE(STATUS "BUILD_TOOLS:       " ${BUILD_TOOLS})
MESSAGE(STATUS "BUILD_TEST:        " ${BUILD_TEST})
MESSAGE(STATUS "")
MESSAGE(STATUS "CYAN_CFG_VERBOSE_ERRORS:        " ${CFG_VERBOSE_ERRORS})
MESSAGE(STATUS "")
MESSAGE(STATUS "*********************************************************")
