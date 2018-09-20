#!/bin/dash

#launch roscore
#xterm -e roscore &

echo ubuntu | sudo -S chmod 666 /dev/ttyUSB0

# sleep 10

#launch the static tfs:
roslaunch /home/ubuntu/git/robo_lape/launchfiles/tf_base_imu.launch &
sleep 1
roslaunch /home/ubuntu/git/robo_lape/launchfiles/tf_base_laser.launch &
sleep 1

#launch the IMU ROS driver:
xterm -hold -e roslaunch /home/ubuntu/git/robo_lape/src/ros_bno055_driver/launch/bosch_bno055_driver.launch &

sleep 5

xterm -e roslaunch rplidar_ros rplidar.launch &

sleep 5 

xterm -hold -e rosrun wheel_odometry_complete wheel_odometry_publisher.py "/dev/ttyACM0" 115200 &

sleep 5

#xterm -e "cd ~/bagfiles && rosbag record odom scan imu/data tf" &

echo "fim"
