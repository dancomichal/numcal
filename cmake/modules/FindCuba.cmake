# - Try to find CUBA
# Once done this will define
#  CUBA_FOUND - System has CUBA
#  CUBA_INCLUDE_DIRS - The CUBA include directories
#  CUBA_LIBRARIES - The libraries needed to use CUBA


find_path(CUBA_INCLUDE_DIR cuba.h
          HINTS /usr/include
          PATH_SUFFIXES CUBA )

find_library(CUBA_LIBRARY NAMES cuba CUBA
             HINTS /usr/lib64 )

set(CUBA_LIBRARIES ${CUBA_LIBRARY} )
set(CUBA_INCLUDE_DIRS ${CUBA_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CUBA_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CUBA  DEFAULT_MSG
                                  CUBA_LIBRARY CUBA_INCLUDE_DIR)

mark_as_advanced(CUBA_INCLUDE_DIR CUBA_LIBRARY )

