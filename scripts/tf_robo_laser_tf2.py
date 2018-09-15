#!/usr/bin/env python  

#base code -> 

import rospy

# Because of transformations
import tf_conversions

import tf2_ros
import geometry_msgs.msg


def laser_relative_pose():
    rospy.init_node('laser_relative_pose', anonymous=False)
    br = tf2_ros.TransformBroadcaster()
    
    t.transform.translation = (-0.07,0.0,0.545)
    
    q = tf_conversions.transformations.quaternion_about_axis(-math.pi * 0.5, (0, 1, 0))
    t.transform.rotation.x = q[0]
    t.transform.rotation.y = q[1]
    t.transform.rotation.z = q[2]
    t.transform.rotation.w = q[3]
