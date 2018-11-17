#!/usr/bin/env python

import rospy
import math
from geometry_msgs.msg import Twist
import sys, select, termios, tty

def getKey():
   tty.setraw(sys.stdin.fileno())
   select.select([sys.stdin], [], [], 0)
   key = sys.stdin.read(1)
   termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
   return key

def go_forward(msg):
    msg.linear.x = 0.5
    msg.angular.z = 0.0
    pub.publish(msg)

def go_backward(msg):
    msg.linear.x = -0.5
    msg.angular.z = 0.0
    pub.publish(msg)

def turn_left(msg):
    msg.linear.x = 0.0
    msg.angular.z = math.pi/2.0
    pub.publish(msg)

def turn_right(msg):
    msg.linear.x = 0.0
    msg.angular.z = -math.pi/2.0
    pub.publish(msg)

def stop(msg):
    msg.linear.x = 0.0
    msg.angular.z = 0.0
    pub.publish(msg)


def talker():
    global pub
    global rate

    pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)

    rospy.init_node('talker', anonymous=True)

    msg = Twist()

    rate = rospy.Rate(100) # 10hz
    
    key = ""
    print("Use W,A,S,D and Space to move the robot")
    while not rospy.is_shutdown():
        key = "x"
        key = getKey()
        key = key.lower()
        if(key == 'w'):
            go_forward(msg)
        elif(key == 's'):
            go_backward(msg)
        elif(key == 'a'):
            turn_left(msg)
        elif(key == 'd'):
            turn_right(msg)
        elif(key == ' '):
            stop(msg)
        elif(key == '\x03'):
            break

        rate.sleep()

if __name__ == '__main__':
    try:
        settings = termios.tcgetattr(sys.stdin)
        talker()
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    except rospy.ROSInterruptException:
        pass
