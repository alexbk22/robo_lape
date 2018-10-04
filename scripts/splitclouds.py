#!/usr/bin/env python

import os

file = open(str(os.environ['HOME'])+"/git/robo_lape/clouds/cloud.txt","r")
# /home/kaue/git/robo_lape/clouds/cloud.txt


count = 5000

n = 0
i = 0

# temp_out = open(str(os.environ['HOME'])+"/git/robo_lape/clouds/cloud1/cloud1_"+str(n)+".txt","w")


for line in file:
    if (i%count == 0):
        n = n + 1
        temp_out = open(str(os.environ['HOME'])+"/git/robo_lape/clouds/cloud1/cloud1_"+str(n)+".txt","w")
        print n

    temp_out.write(line)
    i += 1