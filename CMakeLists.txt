cmake_minimum_required(VERSION 2.8.3)
project(ip_camera_node)



set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  std_msgs
  cv_bridge
  image_transport
  message_generation
)

find_package(OpenCV)

generate_messages(
	DEPENDENCIES
  sensor_msgs
	std_msgs
)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

catkin_package(
	INCLUDE_DIRS
   	LIBRARIES ${PROJECT_NAME}
  	CATKIN_DEPENDS roscpp roslib std_msgs
)

include_directories(${catkin_INCLUDE_DIRS} ${BOOST_INCLUDE_DIR} ${Boost_INCLUDE_DIR} src)
include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(src SRC_LIST)

add_executable(${PROJECT_NAME} src/ip_camera_node.cpp)
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

file(GLOB_RECURSE  LIB_CPP "./src/*.cpp")
file(GLOB_RECURSE  LIB_C "./src/*.c")
file(GLOB_RECURSE  LIB_HDRS "./src/*.h")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall" )