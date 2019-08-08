cmake_minimum_required(VERSION 3.5)

project(health_metric_collector_node)


# Default to C++14
if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif ()


find_package(ament_cmake REQUIRED)
find_package(ament_cmake_gmock REQUIRED)
find_package(rclcpp REQUIRED)
find_package(aws_common REQUIRED)
find_package(aws_ros2_common REQUIRED)
find_package(ros_monitoring_msgs REQUIRED)

add_definitions(-DUSE_IMPORT_EXPORT)

set(HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET ${PROJECT_NAME}_lib)

###########
## Build ##
###########

include_directories(
        include
        ${rclcpp_INCLUDE_DIRS}
        ${aws_ros2_common_INCLUDE_DIRS}
        ${AWSSDK_INCLUDE_DIRS}
        ${aws_common_INCLUDE_DIRS}
        ${ros_monitoring_msgs_INCLUDE_DIRS}
)

add_library(${HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET}
        src/cpu_data.cpp
        src/cpu_metric_collector.cpp
        src/cpu_stats.cpp
        src/metric_manager.cpp
        src/sys_info_collector.cpp
        )

ament_target_dependencies(${HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET}
        rclcpp
        aws_common
        aws_ros2_common
        ros_monitoring_msgs
        rosidl_typesupport_cpp
        )

add_executable(${PROJECT_NAME} src/collector.cpp)

set(LIB_DEPS
        ${rclcpp_LIBRARIES}
        ${aws_common_LIBRARIES}
        ${aws_ros2_common_LIBRARIES}
        ${ros_monitoring_msgs_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${LIB_DEPS})

ament_target_dependencies(${PROJECT_NAME} ${HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET})

target_link_libraries(${PROJECT_NAME} ${HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET})

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME} ${HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        # According to https://answers.ros.org/question/280127/ros2-ros2-run-package-executable-cannot-find-executable/
        # executables are now being installed to the library directory under project name
        RUNTIME DESTINATION lib/${PROJECT_NAME}
        )

## Mark cpp header files for installation
install(
        DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
)

### Mark other files for installation (e.g. launch and bag files, etc.)
install(DIRECTORY launch/ DESTINATION share/${PROJECT_NAME}/launch)
install(DIRECTORY config/ DESTINATION share/${PROJECT_NAME}/config)

#############
## Tests ##
#############

ament_add_gmock(test_health_metric_collector
  test/health_metric_collector_test.cpp)
target_include_directories(test_health_metric_collector
  PRIVATE include)
target_link_libraries(test_health_metric_collector
        ${HEALTH_METRIC_COLLECTOR_LIBRARY_TARGET}
        ${LIB_DEPS})


ament_package()
