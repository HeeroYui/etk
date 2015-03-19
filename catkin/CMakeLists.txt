cmake_minimum_required(VERSION 2.8.3)
project(etk)

set(CMAKE_VERBOSE_MAKEFILE ON)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ../ ../binding_X11
  LIBRARIES ${PROJECT_NAME}
  DEPENDS system_lib
  CFG_EXTRAS ${PROJECT_NAME}-extras.cmake
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ..
  ../binding_X11
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(${PROJECT_NAME}
  ../${PROJECT_NAME}/debug.cpp
  ../${PROJECT_NAME}/stdTools.cpp
  ../${PROJECT_NAME}/log.cpp
  ../${PROJECT_NAME}/tool.cpp
  ../${PROJECT_NAME}/Noise.cpp
  ../${PROJECT_NAME}/Color.cpp
  ../${PROJECT_NAME}/math/Matrix4.cpp
  ../${PROJECT_NAME}/math/Vector2D.cpp
  ../${PROJECT_NAME}/math/Vector3D.cpp
  ../${PROJECT_NAME}/math/Vector4D.cpp
  ../${PROJECT_NAME}/os/FSNode.cpp
  ../${PROJECT_NAME}/os/FSNodeRight.cpp
  ../${PROJECT_NAME}/archive/Archive.cpp
  ../${PROJECT_NAME}/archive/Zip.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 -D__CPP_VERSION__=2011 -D__TARGET_OS__Linux -DETK_EXTERN_FRAMEWORK_ROS")

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY ../${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
