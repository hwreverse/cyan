find_path(LIBTIRPC_INCLUDE_DIR xdr.h DOC "Libtirpc remote procedure call lib"
          HINTS ${LIBTIRPC_ROOT}/include $ENV{LIBTIRPC_ROOT}/include /usr/include
          PATH_SUFFIXES tirpc/rpc libtirpc/rpc )

find_library(LIBTIRPC_LIBRARY NAMES tirpc
          HINTS ${LIBTIRPC_ROOT}/lib 
                ${LIBTIRPC_ROOT}/lib64 
                ${LIBTIRPC_ROOT}/lib32 
                $ENV{LIBTIRPC_ROOT}/lib 
                $ENV{LIBTIRPC_ROOT}/lib64
                $ENV{LIBTIRPC_ROOT}/lib32
          PATH_SUFFIXES tirpc libtirpc )
  
set(LIBTIRPC_INCLUDE_DIRS ${LIBTIRPC_INCLUDE_DIR})
set(LIBTIRPC_LIBRARIES    ${LIBTIRPC_LIBRARY})

# Handle the QUIETLY and REQUIRED arguments and set LIBTIRPC_FOUND to TRUE if
# all listed variables are TRUE.

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBTIRPC DEFAULT_MSG LIBTIRPC_LIBRARIES LIBTIRPC_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBTIRPC_INCLUDE_DIRS LIBTIRPC_LIBRARIES)
