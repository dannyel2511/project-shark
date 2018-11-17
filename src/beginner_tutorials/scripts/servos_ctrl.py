#!/usr/bin/env python
import roslib; roslib.load_manifest('teleop_twist_keyboard')
import rospy

from std_msgs.msg import UInt16

import sys, select, termios, tty

CHANGE_RATE = 3
msg = "Write I, K, O, L"


def getKey():
   tty.setraw(sys.stdin.fileno())
   select.select([sys.stdin], [], [], 0)
   key = sys.stdin.read(1)
   termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
   return key

   


if __name__=="__main__":
   pub1 = rospy.Publisher('servo1', UInt16, queue_size=10)
   pub2 = rospy.Publisher('servo2', UInt16, queue_size=10)

   settings = termios.tcgetattr(sys.stdin)
   
   rospy.init_node('servos_ctrl')
   
   degress1 = 0
   degress2 = 0

   rate = rospy.Rate(100)

   print(msg)
   while(1):
      key = getKey()
      key = key.lower()
      if(key == 'i'):
         degress1 += CHANGE_RATE
      if(key == 'k'):
         degress1 -= CHANGE_RATE
      if(key == 'o'):
         degress2 += CHANGE_RATE
      if(key == 'l'):
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

      if (key == '\x03'):
         break
      rate.sleep()

   termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
   
   


