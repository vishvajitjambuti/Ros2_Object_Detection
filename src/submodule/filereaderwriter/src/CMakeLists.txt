
add_library(fileReaderWriter_lib fileReaderWriter.cpp)

message(${CMAKE_SOURCE_DIR})
target_include_directories(fileReaderWriter_lib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
