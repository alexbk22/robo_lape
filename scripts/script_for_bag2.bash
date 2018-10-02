#!/bin/bash

xterm -e roscore &

sleep 10

# source /home/kaue/catkin_ws/devel/setup.bash
# source /home/lape/catkin_ws/devel/setup.bash
source /home/$USER/catkin_ws/devel/setup.bash


xterm -hold -e roslaunch '/home/'$USER'/git/robo_lape/launchfiles/laser_scan_assembler.launch' &

rosparam set /use_sim_time true

rviz &

BAGNAME='/home/'$USER'/git/robo_lape/rosbags/2018-09-25-21-08-02.bag'

echo $BAGNAME

rosbag play -k --clock $BAGNAME &

sleep 50

# python '/home/'$USER'/git/robo_lape/scripts/laser_assembler_service.py'

rosservice call /assemble_scans 1537921496782000000 1537921513696000000 > cloud.txt


/bin/bash