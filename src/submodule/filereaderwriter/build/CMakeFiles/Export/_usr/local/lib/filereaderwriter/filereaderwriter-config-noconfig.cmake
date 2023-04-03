#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "filereaderwriter::fileReaderWriter_lib" for configuration ""
set_property(TARGET filereaderwriter::fileReaderWriter_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(filereaderwriter::fileReaderWriter_lib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "/usr/local/lib/filereaderwriter/libfileReaderWriter_lib.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS filereaderwriter::fileReaderWriter_lib )
list(APPEND _IMPORT_CHECK_FILES_FOR_filereaderwriter::fileReaderWriter_lib "/usr/local/lib/filereaderwriter/libfileReaderWriter_lib.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
