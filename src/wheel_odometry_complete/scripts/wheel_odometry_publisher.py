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

arduino = serial.Serial(sys.argv[1],sys.argv[2])

rospy.init_node('odometry_publisher')

odom_pub = rospy.Publisher("odom", Odometry, queue_size=50)
odom_broadcaster = tf.TransformBroadcaster()

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

current_time = rospy.Time.now()
last_time = rospy.Time.now()

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
            vdata = map(int,data)
            #print vdata

    
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
    else:
        #left vel
        vl = (vdata[0]*dpp)/varT
        #right vel
        vr = (vdata[1]*dpp)/varT

    vdif = vr-vl
    vsum = vr+vl

    #angular part:
    vth = vdif/base

    delta_th = vth*varT

    th0 = th
    th += delta_th

    th_sin = math.sin(th)
    th_cos = math.cos(th)

    vx = (vsum/2.0)*th_cos
    vy = (vsum/2.0)*th_sin

    delta_x = vx*varT
    delta_y = vy*varT

    if abs(vdata[0]-vdata[1]) > 5 and vdif != 0.0:
        t1 = (base*vsum)/(2.0*vdif)
        delta_x = t1 * (th_sin-math.sin(th0))
        delta_y = t1 * (th_cos-math.cos(th0))

    x += delta_x
    y += delta_y
    

    # since all odometry is 6DOF we'll need a quaternion created from yaw
    odom_quat = tf.transformations.quaternion_from_euler(0, 0, th)

    # first, we'll publish the transform over tf
    odom_broadcaster.sendTransform(
        (x, y, 0.),
        odom_quat,
        current_time,
        "base_link",
        "odom"
    )

    # next, we'll publish the odometry message over ROS
    odom = Odometry()
    odom.header.stamp = current_time
    odom.header.frame_id = "odom"

    # set the position
    odom.pose.pose = Pose(Point(x, y, 0.), Quaternion(*odom_quat))

    # set the velocity
    odom.child_frame_id = "base_link"
    odom.twist.twist = Twist(Vector3(vx, vy, 0), Vector3(0, 0, vth))

    # publish the message
    odom_pub.publish(odom)

    last_time = current_time
    time2_0 = time2
    rate.sleep()
