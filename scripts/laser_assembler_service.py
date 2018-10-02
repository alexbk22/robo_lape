#!/usr/bin/env python
import roslib; roslib.load_manifest('laser_assembler')
import rospy; from laser_assembler.srv import *

out = open("/home/kaue2/git/robo_lape/scripts/cloud.txt","w")

rospy.init_node("test_client")
rospy.wait_for_service("assemble_scans")
try:
    assemble_scans = rospy.ServiceProxy('assemble_scans', AssembleScans)
    resp = assemble_scans(rospy.Time(0,0),rospy.Time(1537921513,0))
    print "Got cloud with %u points" % len(resp.cloud.points)
    for i in range (len(resp.cloud.points)):
        out.write(str(resp.cloud.points[i].x)+","+str(resp.cloud.points[i].y)+","+str(resp.cloud.points[i].z)+"\n")


except rospy.ServiceException, e:
    print "Service call failed: %s"%e