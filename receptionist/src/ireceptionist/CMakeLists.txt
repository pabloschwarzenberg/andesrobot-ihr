cmake_minimum_required(VERSION 3.5)

project(ireceptionist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ireceptionist main.cpp Talk.cpp Ask.cpp MoveTo.cpp Remember.cpp See.cpp CheckNode.cpp)

find_package(ament_cmake QUIET)
find_package(behaviortree_cpp REQUIRED)
find_package(nlp_interfaces REQUIRED)
find_package(vision_interfaces REQUIRED)
find_package(behaviortree_ros2 REQUIRED)
find_package(btcpp_ros2_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

set(dependencies
behaviortree_cpp
behaviortree_ros2
nlp_interfaces
vision_interfaces
)

include_directories(include/nlp_interfaces)
include_directories(include/vision_interfaces)
include_directories(include/behaviortree_ros2)

if(ament_cmake_FOUND)

    ament_target_dependencies(ireceptionist ${dependencies})

elseif( CATKIN_DEVEL_PREFIX OR CATKIN_BUILD_BINARY_PACKAGE)

    find_package(catkin REQUIRED COMPONENTS behaviortree_cpp)
    catkin_package(CATKIN_DEPENDS behaviortree_cpp)
    target_include_directories(ireceptionist PRIVATE ${catkin_INCLUDE_DIRS})
    target_link_libraries(ireceptionist ${catkin_LIBRARIES})

else()

    target_link_libraries(ireceptionist ${dependencies})

endif()

