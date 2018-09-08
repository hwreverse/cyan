

find_path(LAPACKE_INCLUDE_DIR lapacke.h DOC "C-interface to LAPACK"
          HINTS ${LAPACKE_ROOT}/include $ENV{LAPACKE_ROOT}/include /usr/include
          PATH_SUFFIXES lapack lapacke)

find_library(LAPACKE_LIBRARY NAMES lapacke reflapacke
          HINTS ${LAPACKE_ROOT}/lib 
                ${LAPACKE_ROOT}/lib64 
                ${LAPACKE_ROOT}/lib32 
                $ENV{LAPACKE_ROOT}/lib 
                $ENV{LAPACKE_ROOT}/lib64
                $ENV{LAPACKE_ROOT}/lib32
          PATH_SUFFIXES lapack lapacke)
  
find_library(LAPACK_LIBRARY NAMES lapack reflapack
          HINTS ${LAPACKE_ROOT}/lib 
                ${LAPACKE_ROOT}/lib64 
                ${LAPACKE_ROOT}/lib32 
                $ENV{LAPACKE_ROOT}/lib 
                $ENV{LAPACKE_ROOT}/lib64
                $ENV{LAPACKE_ROOT}/lib32
          PATH_SUFFIXES lapack lapacke)

      find_library(BLAS_LIBRARY NAMES blas refblas
          HINTS ${LAPACKE_ROOT}/lib 
                ${LAPACKE_ROOT}/lib64 
                ${LAPACKE_ROOT}/lib32 
                $ENV{LAPACKE_ROOT}/lib 
                $ENV{LAPACKE_ROOT}/lib64
                $ENV{LAPACKE_ROOT}/lib32
          PATH_SUFFIXES lapack lapacke)

set(LAPACKE_INCLUDE_DIRS ${LAPACKE_INCLUDE_DIR})
set(LAPACKE_LIBRARIES    ${LAPACKE_LIBRARY} ${LAPACK_LIBRARY} ${BLAS_LIBRARY})

# Handle the QUIETLY and REQUIRED arguments and set LAPACKE_FOUND to TRUE if
# all listed variables are TRUE.

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LAPACKE DEFAULT_MSG LAPACKE_LIBRARIES LAPACKE_INCLUDE_DIRS)

MARK_AS_ADVANCED(LAPACKE_INCLUDE_DIRS LAPACKE_LIBRARIES)
