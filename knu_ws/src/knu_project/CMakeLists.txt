cmake_minimum_required(VERSION 3.0.2)
project(knu_project)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  std_msgs
  actionlib
  move_base_msgs
)

find_package(Boost REQUIRED COMPONENTS system)


catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES knu_project
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/knu_project.cpp
# )

set (SRC ${SRC}
src/my_setting_nav_goal2.cpp
)

link_libraries(${catkin_LIBRARIES} )

#add_executable(${PROJECT_NAME}_node src/knu_project_node.cpp)
add_executable(key_navigation ${SRC})
add_executable(key_navigation_test src/goal_test.cpp)
# add_executable()
# add_executable(key_navigation src/simple_navigation_goals.cpp)
