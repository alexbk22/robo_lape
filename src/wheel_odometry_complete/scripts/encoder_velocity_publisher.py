#!/usr/bin/env python
#base code: https://gist.github.com/atotto/f2754f75bedb6ea56e3e0264ec405dcf
# thank you atotto 

#exemple of running wiht port "/dev/ttyACM0" and baudrate 115200 :
# rosrun wheel_odometry_complete wheel_odometry_publisher.py "/dev/ttyACM0" 115200

import serial
import sys

import math
from math import sin, cos, pi

import rospy
import tf
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3
from numpy.ma.core import abs

try:
    arduino = serial.Serial(sys.argv[1],sys.argv[2])
except:
    print "could not open Arduino Board at "+sys.argv[1]
    sys.exit(-1)

rospy.init_node('odometry_publisher')

odom_pub = rospy.Publisher("odom", Odometry, queue_size=50)
# odom_broadcaster = tf.TransformBroadcaster()

print "wheel odometer data"


################# CONSTANTES #########################

#pulses per round
ppr = 663.0

#diam in cm, to be converted
diam = 13.5 
diam /= 100.0

#espessura das rodas
er = 2.1
er /= 100.0

#base entre o centro das rodas
base = 30.0
base /= 100.0
base -= er


r = diam/2

circum = math.pi * diam

#distance per pulse
dpp = circum/ppr

#######################################################

x = 0.0
y = 0.0
th = 0.0

vx = 0.0
vy = 0.0
vth = 0.0

vl = 0.0
vr = 0.0

dl = 0.0
dr = 0.0

current_time = rospy.Time.now()
# last_time = rospy.Time.now()

time2_0 = 0.0
time2   = 0.0

#we cannot handle empty data
vdata = [0.0,0.0,0.0]

rate = rospy.Rate(60)
while not rospy.is_shutdown():
    current_time = rospy.Time.now()
    
    data = str(arduino.readline())
    data = data[:-2].split(',')
    if len(data) == 3:
        if data[0] != '' and data[1] != '' and data[2] != '':
            try:
                vdata = map(int,data)
            except:
                print "except"
                vdata = [0.0,0.0,0.0]
    
    #vdata = [10,20,1000]

    time2 = vdata[2]

    #time variation #TO_MODIFY 
    #vart = (time2 - time2_0)/1000000.0
    varT = (current_time - last_time).to_sec()
    if varT > 1.0:
        varT = 0.0

    if varT == 0.0:
        vl = 0.0
        vr = 0.0
        dl = 0.0
        dr = 0.0
    else:
        dl = vdata[0]*dpp
        dr = vdata[1]*dpp
        #left vel
        vl = dl/varT
        #right vel
        vr = dr/varT

    vdiff = vr-vl
    vsum =  vr+vl

    vm  = vsum * 0.5
    vth = vdiff * 0.5

    # next, we'll publish the odometry message over ROS
    odom = Odometry()
    odom.header.stamp = current_time
    odom.header.frame_id = "odom_fake"

    odom.pose.pose = Pose(Vector3(0.0,0.0,0.0),Quaternion(0.0,0.0,0.0,1.0))

    odom.pose.covariance[0]  = 1.0
    odom.pose.covariance[7]  = 1.0
    odom.pose.covariance[14] = 1.0

    odom.pose.covariance[21] = 1.0
    odom.pose.covariance[28] = 1.0
    odom.pose.covariance[35] = 1.0

    odom.twist.twist = Twist(Vector3(vm, 0.0, 0.0), Vector3(0.0, 0.0, vth))


    odom.twist.covariance[0]  = 0.001
    odom.twist.covariance[7]  = 0.000001
    odom.twist.covariance[14] = 1.0

    odom.twist.covariance[21] = 1.0
    odom.twist.covariance[28] = 1.0
    odom.twist.covariance[35] = 0.01

    odom_pub.publish(odom)
    rate.sleep()

