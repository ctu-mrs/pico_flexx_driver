cmake_minimum_required(VERSION 3.5.2)
project(pico_flexx2_driver)

find_package(royale 5 REQUIRED
  PATHS ${PROJECT_SOURCE_DIR}/libroyale-5.9.0.2568-LINUX-x86-64Bit/lib/cmake
)

set(royale_sdk_include_dirs royale::royale)
set(royale_sdk_libraries royale::royale)

find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  rostime
  sensor_msgs
  std_msgs
  dynamic_reconfigure
  pico_flexx_msgs
)

# combine cmake_cxx_flags and additional_cxx_flags
# plus change the space-separated string, into a list delimited by semicolons
# cxx_flags will be used with target_compile_options (cleaner than changing CMAKE_CXX_FLAGS) 
string(REPLACE " " ";" cxx_flags "${CMAKE_CXX_FLAGS} ${additional_cxx_flags}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# debugging output
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
MESSAGE( STATUS "additional_cxx_flags: " ${additional_cxx_flags})
MESSAGE( STATUS "cxx_flags: ${cxx_flags}")
MESSAGE( STATUS "royale version: ${royale_VERSION}")


###################################
## catkin specific configuration ##
###################################

catkin_package(
  CATKIN_DEPENDS nodelet roscpp rostime sensor_msgs std_msgs dynamic_reconfigure pico_flexx_msgs
)

###########
## Build ##
###########


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${royale_sdk_include_dirs}
)

add_library(pico_flexx2_nodelet SHARED ../src/pico_flexx_driver.cpp)
target_link_libraries(pico_flexx2_nodelet
  ${catkin_LIBRARIES}
  ${royale_sdk_libraries}
)

add_dependencies(pico_flexx2_nodelet ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_compile_options(pico_flexx2_nodelet PUBLIC ${cxx_flags})
target_compile_definitions(pico_flexx2_nodelet PUBLIC royale_VERSION_MAJOR=${royale_VERSION_MAJOR} royale_VERSION_MINOR=${royale_VERSION_MINOR})

add_executable(pico_flexx2_driver ../src/pico_flexx_driver.cpp)
target_link_libraries(pico_flexx2_driver
  ${catkin_LIBRARIES}
  ${royale_sdk_libraries}
)
add_dependencies(pico_flexx2_driver ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_compile_options(pico_flexx2_driver PUBLIC ${cxx_flags})
target_compile_definitions(pico_flexx2_driver PUBLIC royale_VERSION_MAJOR=${royale_VERSION_MAJOR} royale_VERSION_MINOR=${royale_VERSION_MINOR})
