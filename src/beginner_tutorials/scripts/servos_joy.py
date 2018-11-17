#!/usr/bin/env python

import rospy

from std_msgs.msg import UInt16
from sensor_msgs.msg import Joy

global x
global z

CHANGE_RATE = 3

def callback(data):
   global x
   global z
   global degress1
   global degress2

   x = data.axes[6]
   z = data.axes[7]

   if(x > 0.5):
      degress1 += CHANGE_RATE
   if(x < -0.5):
      degress1 -= CHANGE_RATE
   if(z > 0.5):
      degress2 += CHANGE_RATE
   if(z < -0.5):
      degress2 -= CHANGE_RATE

   if degress1< 0:
      degress1=0
   if degress2< 0:
      degress2=0
   if degress1 >180:
      degress1=180
   if degress2> 180:
      degress2=180

   print("Servo 1:",degress1)
   print("Servo 2:",degress2)

   pub1.publish(degress1)
   pub2.publish(degress2)
   
   
def start():
   global degress1
   global degress2
   global pub1
   global pub2

   pub1 = rospy.Publisher('servo1', UInt16, queue_size=10)
   pub2 = rospy.Publisher('servo2', UInt16, queue_size=10)

   rospy.Subscriber("joy", Joy, callback)

   rospy.init_node('servos_ctrl')

   rate = rospy.Rate(100)

   while not rospy.is_shutdown():
      rate.sleep()


   
   
   

if __name__=="__main__":
   global degress1
   global degress2
   global x
   global z
   x=0
   z=0
   degress1 = 0
   degress2 = 0
   start()