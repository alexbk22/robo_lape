#!/bin/bash

source /home/ubuntu/git/robo_lape/devel/setup.bash

rosnode kill $(rosnode list | grep record)