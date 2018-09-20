#!/usr/bin/env python  

import math
import roslib
#roslib.load_manifest('learning_tf')
import rospy

import tf
#import turtlesim.msg

def laser_relative_pose():
    rospy.init_node('laser_relative_pose', anonymous=False)

    quat = tf.transformations.quaternion_about_axis(-math.pi * 0.5, (0, 1, 0))
    print quat
    translation = (-0.07,0.0,0.545)
    br = tf.TransformBroadcaster()
    r = rospy.Rate(0.1)
    while not rospy.is_shutdown():
        br.sendTransform(translation,
                     quat,
                     rospy.Time.now(),
                     "base_link",
                     "base_laser")
        r.sleep()
    

if __name__ == '__main__':
    laser_relative_pose()
    #rospy.spin()
