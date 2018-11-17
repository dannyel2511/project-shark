cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  message_generation
)


## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   Num.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   AddTwoInts.srv
 )


 generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
 )



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime geometry_msgs

)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


# Executables for the talker and listener tutorial
add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

# Executables for the two_wheels_simulator

add_executable(dannyel_talker src/dannyel_talker.cpp)
target_link_libraries(dannyel_talker ${catkin_LIBRARIES})
add_dependencies(dannyel_talker beginner_tutorials_generate_messages_cpp)

add_executable(gomez_listener src/gomez_listener.cpp)
target_link_libraries(gomez_listener ${catkin_LIBRARIES})
add_dependencies(gomez_listener beginner_tutorials_generate_messages_cpp)




