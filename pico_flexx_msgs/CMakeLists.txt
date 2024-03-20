cmake_minimum_required(VERSION 3.5.2)
project(pico_flexx_msgs)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  cfg/pico_flexx_driver.cfg
  cfg/pico_flexx2_driver.cfg
)

catkin_package(
  CATKIN_DEPENDS dynamic_reconfigure 
)
