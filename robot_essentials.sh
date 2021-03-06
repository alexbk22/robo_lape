#!/bin/bash

source /home/ubuntu/git/robo_lape/devel/setup.bash

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

# xterm -hold -e rostopic echo /calib &

sleep 5

xterm -e roslaunch rplidar_ros rplidar.launch &

sleep 5 

xterm -hold -e python /home/ubuntu/git/robo_lape/src/wheel_odometry_complete/scripts/encoder_velocity_publisher.py "/dev/ttyACM0" 115200 &

sleep 5

xterm -hold -e roslaunch /home/ubuntu/git/robo_lape/launchfiles/laser_scan_assembler.launch &

sleep 5

xterm -hold -e roslaunch /home/ubuntu/git/robo_lape/launchfiles/ekf_template.launch &
#xterm -e "cd ~/bagfiles && rosbag record odom scan imu/data tf" &

echo "fim"

/bin/bash