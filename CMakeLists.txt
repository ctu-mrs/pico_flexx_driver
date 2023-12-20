cmake_minimum_required(VERSION 3.5.2)
project(pico_flexx_driver)

set(additional_cxx_flags "-DBT_USE_DOUBLE_PRECISION")

find_package(royale 4 REQUIRED
  PATHS ${PROJECT_SOURCE_DIR}/../libroyale-4.24.0.1201-LINUX-x86-64Bit/share
)
add_definitions(-DSDK_MAJOR_VERSION=4)
link_directories (${royale_LIB_DIR})
set(royale_sdk_include_dirs ${royale_INCLUDE_DIRS})
set(royale_sdk_libraries ${royale_LIBRARIES})

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  rostime
  sensor_msgs
  std_msgs
  dynamic_reconfigure
)

string(REPLACE " " ";" cxx_flags "${CMAKE_CXX_FLAGS} ${additional_cxx_flags}")

# debugging output
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
MESSAGE( STATUS "additional_cxx_flags: " ${additional_cxx_flags})
MESSAGE( STATUS "cxx_flags: ${cxx_flags}")
MESSAGE( STATUS "royale version: ${royale_VERSION}")


################################################
## Declare ROS messages, services and actions ##
################################################

generate_dynamic_reconfigure_options(
  cfg/pico_flexx_driver.cfg
)

###################################
## catkin specific configuration ##
###################################

catkin_package(
  CATKIN_DEPENDS nodelet roscpp rostime sensor_msgs std_msgs dynamic_reconfigure
)

###########
## Build ##
###########


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${royale_sdk_include_dirs}
)

add_library(pico_flexx_nodelet SHARED src/pico_flexx_driver.cpp)
target_link_libraries(pico_flexx_nodelet
  ${catkin_LIBRARIES}
  ${royale_sdk_libraries}
)
add_dependencies(pico_flexx_nodelet ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_compile_options(pico_flexx_nodelet PUBLIC ${cxx_flags})
target_compile_definitions(pico_flexx_nodelet PUBLIC royale_VERSION_MAJOR=${royale_VERSION_MAJOR} royale_VERSION_MINOR=${royale_VERSION_MINOR})

add_executable(pico_flexx_driver src/pico_flexx_driver.cpp)
target_link_libraries(pico_flexx_driver
  ${catkin_LIBRARIES}
  ${royale_sdk_libraries}
)
add_dependencies(pico_flexx_driver ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_compile_options(pico_flexx_driver PUBLIC ${cxx_flags})
target_compile_definitions(pico_flexx_driver PUBLIC royale_VERSION_MAJOR=${royale_VERSION_MAJOR} royale_VERSION_MINOR=${royale_VERSION_MINOR})

