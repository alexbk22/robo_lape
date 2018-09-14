#!/usr/bin/env python  

#base code -> 

import rospy

# Because of transformations
import tf_conversions

import tf2_ros
import geometry_msgs.msg


def laser_relative_pose():
    rospy.init_node('laser_relative_pose', anonymous=False)
    