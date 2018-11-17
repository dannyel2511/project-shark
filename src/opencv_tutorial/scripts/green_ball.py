#!/usr/bin/env python

'''
Track a green ball using OpenCV.

    Copyright (C) 2015 Conan Zhao and Simon D. Levy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
    published by the Free Software Foundation, either version 3 of the 
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License 
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''
import rospy
import cv2
import numpy as np
import time
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from geometry_msgs.msg import Twist

# For OpenCV2 image display
WINDOW_NAME = 'GreenBallTracker' 

def nothing(x):
    pass

def get_image_callback(data):

    global ready
    bridge = CvBridge()
    try:
      cv_image = bridge.imgmsg_to_cv2(data, "bgr8")
    except CvBridgeError as e:
      print(e)
    #image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
    if(ready):
        track(cv_image) 
        ready = False


def track(image):

    '''Accepts BGR image as Numpy array
       Returns: (x,y) coordinates of centroid if found
                (-1,-1) if no centroid was found
                None if user hit ESC
    '''
    cv2.namedWindow('sliders',cv2.WINDOW_NORMAL)

    # create trackbars for color change
    cv2.createTrackbar('H_MIN','sliders',0,255,nothing)
    cv2.createTrackbar('S_MIN','sliders',0,255,nothing)
    cv2.createTrackbar('V_MIN','sliders',0,255,nothing)
    cv2.createTrackbar('H_MAX','sliders',0,255,nothing)
    cv2.createTrackbar('S_MAX','sliders',0,255,nothing)
    cv2.createTrackbar('V_MAX','sliders',0,255,nothing)

    H_MIN = cv2.getTrackbarPos('H_MIN','sliders')
    S_MIN = cv2.getTrackbarPos('S_MIN','sliders')
    V_MIN = cv2.getTrackbarPos('V_MIN','sliders')
    H_MAX = cv2.getTrackbarPos('H_MAX','sliders')
    S_MAX = cv2.getTrackbarPos('S_MAX','sliders')
    V_MAX = cv2.getTrackbarPos('V_MAX','sliders')


    H_MIN = 14
    S_MIN = 47
    V_MIN = 66
    H_MAX = 76
    S_MAX = 180
    V_MAX = 232

    
    #cv2.imshow('sliders',img)


    # Blur the image to reduce noise
    blur = cv2.GaussianBlur(image, (5,5),0)
    # Convert BGR to HSV
    hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)

    # Threshold the HSV image for only green colors
    lower_green = np.array([H_MIN,S_MIN,V_MIN])
    upper_green = np.array([H_MAX,S_MAX,V_MAX])

    # Threshold the HSV image to get only green colors
    mask = cv2.inRange(hsv, lower_green, upper_green)
    
    # Blur the mask
    bmask = cv2.GaussianBlur(mask, (5,5),0)

    cv2.imshow("sliders", bmask)
    cv2.resizeWindow('sliders', 600,600)

    # Draw contours
    cnts = cv2.findContours(bmask,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    print("---------------")
    ##print(cnts)
    print("++++++++++++++++")
    cnts = cnts[1]
    #print(cnts)
    area = 0

    if len(cnts) > 0:
        # find the largest contour in the mask, then use
        # it to compute the minimum enclosing circle and
        # centroid
        c = max(cnts, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

                # only proceed if the radius meets a minimum size
        if radius > 10:
            area = 3.141592 * radius * radius
            print(area)
            # draw the circle and centroid on the frame,
            # then update the list of tracked points
            cv2.circle(image, (int(x), int(y)), int(radius),
                (0, 255, 255), 2)
            cv2.circle(image, center, 5, (0, 0, 255), -1)

    objArea = 0
    objX = 0
    objY = 0
    
    # Take the moments to get the centroid
    moments = cv2.moments(bmask)
    m00 = moments['m00']

    centroid_x, centroid_y = None, None
    if m00 != 0:
        centroid_x = int(moments['m10']/m00)
        centroid_y = int(moments['m01']/m00)

    # Assume no centroid
    ctr = (-1,-1)

    # Use centroid if it exists
    if centroid_x != None and centroid_y != None:

        ctr = (centroid_x, centroid_y)

        # Put black circle in at centroid in image
        cv2.circle(image, ctr, 4, (0,0,0))

    # Display full-color image
    cv2.imshow(WINDOW_NAME, image)

    # Force image display, setting centroid to None on ESC key input
    if cv2.waitKey(1) & 0xFF == 27:
        ctr = None
    
    # Return coordinates of centroid
    rango = 40000
    twist = Twist()
    if(area < rango):
        print("avanzando")
        twist.angular.y = 0
        twist.linear.x = 255
        pub.publish(twist)
        time.sleep(0.5)

        twist.linear.y = 255
        pub.publish(twist)
        time.sleep(0.5)

        twist.linear.x = 0
        twist.linear.y = 0
        pub.publish(twist)
    else:
        twist.angular.y = 1000
        print("buzzer!!!!!!!")
    return ctr


# Test with input from camera
if __name__ == '__main__':
    global pub
    global ready

    ready = False

    
    
    rospy.Subscriber("image_raw",Image,get_image_callback)
    pub = rospy.Publisher('motors', Twist, queue_size=10)
    rospy.init_node('green_ball', anonymous=True)

    rate = rospy.Rate(100)
    while not rospy.is_shutdown():
        time.sleep(0.2)
        ready=True
        #rospy.spin()

