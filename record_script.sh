#!/bin/dash

xterm -e "cd ~/bagfiles && rosbag record odom scan imu/data tf" &

#xterm -e "cd ~/bagfiles && rosbag -a" &