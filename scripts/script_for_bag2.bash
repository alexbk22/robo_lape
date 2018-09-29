#!/bin/bash

xterm -e roscore &

sleep 10

# source /home/kaue/catkin_ws/devel/setup.bash
# source /home/lape/catkin_ws/devel/setup.bash
source /home/$USER/catkin_ws/devel/setup.bash


rosparam set /use_sim_time true

rviz &

BAGNAME='/home/'$USER'/git/robo_lape/rosbags/2018-09-25-21-08-02.bag'

echo $BAGNAME

rosbag play --clock $BAGNAME &

/bin/bash