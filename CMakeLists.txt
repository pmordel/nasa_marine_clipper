cmake_minimum_required(VERSION 2.8.3)
project(nasa_marine_clipper)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  nmea_msgs
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Anemometer.msg
)

generate_messages(
  DEPENDENCIES
  nmea_msgs
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES nasa_marine_clipper
 CATKIN_DEPENDS nmea_msgs roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/nasa_marine_clipper.cpp
# )


#add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(${PROJECT_NAME}_node src/nasa_marine_clipper_node.cpp)

# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)
