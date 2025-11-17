cmake_minimum_required(VERSION 3.5)

project(receptionist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(receptionist main.cpp say.cpp)

find_package(ament_cmake QUIET)

if(ament_cmake_FOUND)

    find_package(behaviortree_cpp_v3 REQUIRED)
    ament_target_dependencies(receptionist behaviortree_cpp_v3)

elseif( CATKIN_DEVEL_PREFIX OR CATKIN_BUILD_BINARY_PACKAGE)

    find_package(catkin REQUIRED COMPONENTS behaviortree_cpp_v3)
    catkin_package(CATKIN_DEPENDS behaviortree_cpp_v3)
    target_include_directories(receptionist PRIVATE ${catkin_INCLUDE_DIRS})
    target_link_libraries(receptionist ${catkin_LIBRARIES})

else()

    find_package(behaviortree_cpp_v3 REQUIRED)
    target_link_libraries(receptionist behaviortree_cpp_v3)

endif()

