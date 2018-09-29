find_path(LIBNETPBM_INCLUDE_DIR pam.h DOC "Libnetpbm Image processing library"
          HINTS ${LIBNETPBM_ROOT}/include $ENV{LIBNETPBM_ROOT}/include /usr/include
          PATH_SUFFIXES netpbm libnetpbm )

find_library(LIBNETPBM_LIBRARY NAMES netpbm
          HINTS ${LIBNETPBM_ROOT}/lib 
                ${LIBNETPBM_ROOT}/lib64 
                ${LIBNETPBM_ROOT}/lib32 
                $ENV{LIBNETPBM_ROOT}/lib 
                $ENV{LIBNETPBM_ROOT}/lib64
                $ENV{LIBNETPBM_ROOT}/lib32
          PATH_SUFFIXES netpbm libnetpbm )
  
set(LIBNETPBM_INCLUDE_DIRS ${LIBNETPBM_INCLUDE_DIR})
set(LIBNETPBM_LIBRARIES    ${LIBNETPBM_LIBRARY})

# Handle the QUIETLY and REQUIRED arguments and set LIBNETPBM_FOUND to TRUE if
# all listed variables are TRUE.

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBNETPBM DEFAULT_MSG LIBNETPBM_LIBRARIES LIBNETPBM_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBNETPBM_INCLUDE_DIRS LIBNETPBM_LIBRARIES)
