#!/usr/bin/env python

import rospy

from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

def callback(data):
   twist = Twist()
   #Get data to control the direction of the robot
   twist.linear.x = 255*data.axes[1]
   twist.angular.z = 255*data.axes[0]
   #Get data to control the speed of the wheels in the middle
   twist.linear.y = 255*data.axes[5]

   if(twist.linear.y > 0):
      twist.linear.y = 255 - twist.linear.y
   else:
      twist.linear.y = twist.linear.y * -1 + 255
   
   twist.linear.y = twist.linear.y * 0.5

   print("x",twist.linear.x)
   print("z",twist.angular.z)
   print("vel_mid", twist.linear.y)
   pub.publish(twist)


def start():
   global pub
   
   pub = rospy.Publisher('motors', Twist, queue_size=10)
   rospy.Subscriber("joy", Joy, callback)
   
   rospy.init_node('motors_ctrl')

   rate = rospy.Rate(100)

   #while not rospy.is_shutdown():
   #   rate.sleep()
   rospy.spin()

if __name__ == '__main__':
        start()
