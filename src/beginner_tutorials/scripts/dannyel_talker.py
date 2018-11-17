#!/usr/bin/env python

import rospy
import math
from geometry_msgs.msg import Twist

def go_forward(msg):
    msg.linear.x = 0.5
    msg.angular.z = 0.0
    for i in range(0,5):
        pub.publish(msg)
        rate.sleep()

def go_backward(msg):
    msg.linear.x = -0.5
    msg.angular.z = 0.0
    for i in range(0,5):
        pub.publish(msg)
        rate.sleep()
def turn_left(msg):
    msg.linear.x = 0.0
    msg.angular.z = math.pi/2.0
    for i in range(0,5):
        pub.publish(msg)
        rate.sleep()
def turn_right(msg):
    msg.linear.x = 0.0
    msg.angular.z = -math.pi/2.0
    for i in range(0,5):
        pub.publish(msg)
        rate.sleep()

def stop(msg):
    msg.linear.x = 0.0
    msg.angular.z = 0.0




def talker():
    global pub
    global rate

    pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)

    rospy.init_node('talker', anonymous=True)

    msg = Twist()

    rate = rospy.Rate(1) # 10hz
    

    while not rospy.is_shutdown():
        go_forward(msg)
        stop(msg)
        go_backward(msg)
        stop(msg)
        turn_right(msg)
        stop(msg)
        turn_left(msg)
        stop(msg)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
