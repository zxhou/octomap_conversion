cmake_minimum_required(VERSION 3.0.2)
project(rospy_rviz)

add_compile_options(-std=c++14)
set(CMAKE_BUILD_TYPE "Release")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  nav_msgs
  message_generation
  std_msgs
  octomap_ros
)
find_package(octomap REQUIRED)

#target_link_libraries(${OCTOMAP_LIBRARIES})
#find_package(Eigen3 REQUIRED)
catkin_package(
    CATKIN_DEPENDS octomap_ros
)
 
#find_package(catkin REQUIRED COMPONENTS
#    message_generation
 #   std_msgs
 #   )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
include_directories(
  ${OCTOMAP_INCLUDE_DIRS}
)


find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
    
# do not wildcard install files since the root folder of the package will contain a debian folder for releasing
catkin_install_python(PROGRAMS
  script/rospy_rviz.py
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/rospy_rviz
)
install(FILES
  launch/rospy_rviz.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/rospy_rviz
)

add_executable(${PROJECT_NAME}_node src/ogm.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OCTOMAP_LIBRARIES})
#target_link_libraries()