#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt16

def talker():
    pub = rospy.Publisher('servo1', UInt16, queue_size=10)
    pub2 = rospy.Publisher('servo2', UInt16, queue_size=10)

    rospy.init_node('talker', anonymous=True)

    rate = rospy.Rate(1) # 10hz
    degrees = 0.0
    while not rospy.is_shutdown():
        degrees += 10
        degrees %= 360
        rospy.loginfo(degrees)
        pub.publish(degrees)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
