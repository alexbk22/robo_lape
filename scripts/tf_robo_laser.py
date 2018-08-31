#!/usr/bin/env python  

import roslib
#roslib.load_manifest('learning_tf')
import rospy

import tf
#import turtlesim.msg

def laser_relative_pose():
    rospy.init_node('laser_relative_pose', anonymous=False)

    quat = quaternion_about_axis(-math.pi * 0.5, (0, 1, 0))
    translation = (-0.07,0.0,0.545)
    br = tf.TransformBroadcaster()
    br.sendTransform(translation,
                     quat,
                     rospy.Time.now(),
                     "base_link",
                     "base_laser")

if __name__ == '__main__':
    laser_relative_pose():
    rospy.spin()
