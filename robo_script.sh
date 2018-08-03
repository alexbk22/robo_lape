#!/bin/bash

#launch roscore
xterm -e roscore &

sleep 10

#launching the IMU ROS driver:
xterm -e roslaunch /home/pi/git/robo_lape/src/ros_bno055_driver/launch/bosch_bno055_driver.launch &

sleep 10

xterm -e roslaunch rplidar_ros rplidar.launch &

echo "fim"
