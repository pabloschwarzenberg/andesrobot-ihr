cmake_minimum_required(VERSION 3.5)

project(btcpp_sample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(btcpp_sample main.cpp)

find_package(ament_cmake QUIET)

if(ament_cmake_FOUND)

    find_package(behaviortree_cpp_v3 REQUIRED)
    ament_target_dependencies(btcpp_sample behaviortree_cpp_v3)

elseif( CATKIN_DEVEL_PREFIX OR CATKIN_BUILD_BINARY_PACKAGE)

    find_package(catkin REQUIRED COMPONENTS behaviortree_cpp_v3)
    catkin_package(CATKIN_DEPENDS behaviortree_cpp_v3)
    target_include_directories(btcpp_sample PRIVATE ${catkin_INCLUDE_DIRS})
    target_link_libraries(btcpp_sample ${catkin_LIBRARIES})

else()

    find_package(behaviortree_cpp_v3 REQUIRED)
    target_link_libraries(btcpp_sample behaviortree_cpp_v3)

endif()

