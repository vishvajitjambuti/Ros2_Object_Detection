cmake_minimum_required(VERSION 3.09)
project(filereaderwriter VERSION "${VERSION}")  ##Projectname
set(CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
find_package(OpenCV REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp  include/fileReaderWriter.h)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
            fileReaderWriter_lib
            ${OpenCV_LIBS})

########installation folders##########
    #headers: 	/usr/local/include/
    #libs: 	/usr/local/lib/

install (FILES include/fileReaderWriter.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})

install( TARGETS
            fileReaderWriter_lib
        EXPORT
            export_fileReaderWriter
        DESTINATION
        ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_PROJECT_NAME})

install(EXPORT
            export_fileReaderWriter
        NAMESPACE
            ${CMAKE_PROJECT_NAME}::
        FILE
            ${CMAKE_PROJECT_NAME}-config.cmake
        DESTINATION
            ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_PROJECT_NAME})
