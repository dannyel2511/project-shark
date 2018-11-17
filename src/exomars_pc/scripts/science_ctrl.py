#!/usr/bin/env python

import rospy

from std_msgs.msg import Bool
from std_msgs.msg import String
from sensor_msgs.msg import Joy

def callback(data):
   button = Bool() 
   button.data = data.buttons[1]
   pub.publish(button)

def info_cb(data):
   print(data.data)


def start():
   global pub
   
   pub = rospy.Publisher('science', Bool, queue_size=10)
   rospy.Subscriber("joy", Joy, callback)
   rospy.Subscriber("science_info", String, info_cb)
   
   rospy.init_node('science_ctrl')

   rate = rospy.Rate(100)

   rospy.spin()

if __name__ == '__main__':
        start()
