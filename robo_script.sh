#!/bin/bash

#launch roscore
xterm -e roscore &

sleep 5

#launching the IMU ROS driver:
xterm -hold -e roslaunch /home/pi/git/robo_lape/src/ros_bno055_driver/launch/bosch_bno055_driver.launch &

sleep 5

xterm -e roslaunch rplidar_ros rplidar.launch &

sleep 5 

xterm -hold -e rosrun wheel_odometry_complete wheel_odometry_publisher.py "/dev/ttyACM0" 115200 &

echo "fim"
