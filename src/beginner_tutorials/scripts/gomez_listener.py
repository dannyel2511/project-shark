#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist

def callback(data):
    text = ""
    if(data.linear.x > 0): 
        text = "GOING FORWARD"
    elif(data.linear.x < 0):
        text = "GOING BACKWARD"
    elif(data.angular.z > 0):
        text = "TURNING LEFT"
    else:
        text = "TURNING RIGHT"


    rospy.loginfo(rospy.get_caller_id() + text)

def listener():

    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber('cmd_vel', Twist, callback)

    rospy.spin()

if __name__ == '__main__':
    listener()
