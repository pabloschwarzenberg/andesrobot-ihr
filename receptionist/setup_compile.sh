#sudo apt-get install ros-humble-behaviortree-cpp-v3
#dpkg -L ros-humble-behaviortree-cpp-v3
#sudo apt install ros-humble-ament-cmake-python
#sudo apt install python3-ament-package
#source /opt/ros/humble/setup.bash
colcon version-check
#export CMAKE_PREFIX_PATH=/opt/ros/humble/share/behaviortree_cpp_v3/cmake:$CMAKE_PREFIX_PATH
colcon build
