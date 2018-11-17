#!/usr/bin/env python

import rospy

from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

def callback(data):
   twist = Twist()
   twist.linear.x = 255*data.axes[1]
   twist.angular.z = 255*data.axes[0]
   print("x",twist.linear.x)
   print("z",twist.angular.z)
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