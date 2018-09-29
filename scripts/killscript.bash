
#!/bin/bash

source /home/$USER/catkin_ws/devel/setup.bash

rosnode kill -a

killall -9 roscore

killall -9 rosmaster

killall xterm

/bin/bash