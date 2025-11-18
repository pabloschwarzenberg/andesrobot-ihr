cmake_minimum_required(VERSION 3.5)

project(receptionist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(receptionist main.cpp Talk.cpp MoveTo.cpp Remember.cpp See.cpp ActionClient.cpp)

find_package(ament_cmake QUIET)
find_package(behaviortree_cpp_v3 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(nlp_interfaces REQUIRED)

set(dependencies
behaviortree_cpp_v3
rclcpp
rclcpp_action
rclcpp_components
nlp_interfaces
)

include_directories(include/nlp_interfaces)

if(ament_cmake_FOUND)

    ament_target_dependencies(receptionist ${dependencies})

elseif( CATKIN_DEVEL_PREFIX OR CATKIN_BUILD_BINARY_PACKAGE)

    find_package(catkin REQUIRED COMPONENTS behaviortree_cpp_v3)
    catkin_package(CATKIN_DEPENDS behaviortree_cpp_v3)
    target_include_directories(receptionist PRIVATE ${catkin_INCLUDE_DIRS})
    target_link_libraries(receptionist ${catkin_LIBRARIES})

else()

    target_link_libraries(receptionist ${dependencies})

endif()

