
#!/bin/sh

# source /home/kaue/catkin_ws/devel/setup.sh
source /home/lape/catkin_ws/devel/setup.sh


rosnode kill -a

killall -9 roscore

killall -9 rosmaster

killall xterm