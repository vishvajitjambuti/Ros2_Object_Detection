cmake_minimum_required(VERSION 3.0)
project(camera_cpp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
# https://github.com/vector-of-bool/pmm/issues/17
cmake_policy(SET CMP0057 NEW)

#if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#  add_compile_options(-Wall -Wextra -Wpedantic)
#endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(filereaderwriter REQUIRED)

include(FetchContent)
include_directories(
        ${OpenCV_INCLUDE_DIRS}
)

file(GLOB SOURCES src/camera.cpp)
add_executable(camera_publisher src/camera_publisher.cpp ${SOURCES})
ament_target_dependencies(camera_publisher
        PUBLIC
        rclcpp
        sensor_msgs
        )
target_link_libraries(camera_publisher
        PUBLIC
        ${OpenCV_LIBS}
        filereaderwriter::fileReaderWriter_lib
        )

add_executable(camera_subscriber src/camera_subscriber.cpp ${SOURCES})
ament_target_dependencies(camera_subscriber
        PUBLIC
        rclcpp
        sensor_msgs
        )
target_link_libraries(camera_subscriber
        PUBLIC
        ${OpenCV_LIBS}
        filereaderwriter::fileReaderWriter_lib
        )

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
        camera_publisher
        DESTINATION lib/${PROJECT_NAME}
        )
install(TARGETS
        camera_subscriber
        DESTINATION lib/${PROJECT_NAME}
        )

ament_package()
