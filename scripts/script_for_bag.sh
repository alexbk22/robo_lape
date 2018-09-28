#!/bin/bash

xterm -e roscore &

sleep 10

source /home/kaue/catkin_ws/devel/setup.bash

# rviz &

rosparam set /use_sim_time true

# sleep 10

rosrun rviz rviz -d /home/kaue/git/robo_lape/parameterfiles/rviz_config.rviz &

# sleep 5

# roslaunch /home/kaue/catkin_ws/src/hector_laserscan_to_pointcloud/launch/laserscan_to_pointcloud_shadow_filtered.launch &

sleep 5

xterm -hold -e roslaunch /home/kaue/git/robo_lape/launchfiles/tf_base_imu.launch &
xterm -hold -e roslaunch /home/kaue/git/robo_lape/launchfiles/tf_base_laser.launch &
xterm -hold -e roslaunch /home/kaue/git/robo_lape/launchfiles/laser_scan_assembler.launch &

sleep 2

xterm -hold -e roslaunch /home/kaue/git/robo_lape/launchfiles/ekf_template.launch &

sleep 2

rosbag play -k -d 8 --clock /home/kaue/git/robo_lape/rosbags/2018-09-20-19-57-08.bag &
# rosbag play /home/kaue/git/robo_lape/rosbags/2018-09-20-19-57-08.bag

sleep 10

python /home/kaue/git/robo_lape/scripts/laser_assembler_service.py

/bin/bash