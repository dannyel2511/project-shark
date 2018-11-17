#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

void chatterCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  if(msg->linear.x > 0) {
      ROS_INFO("GOING FORWARD");
  }
  if(msg->linear.x < 0) {
      ROS_INFO("GOING BACKWARD");
  }
  if(msg->angular.z < 0) {
      ROS_INFO("TURNING RIGHT");
  }
  if(msg->angular.z > 0) {
      ROS_INFO("TURNING LEFT");
  }
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "gomez_listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("cmd_vel", 1000, chatterCallback);

  ros::spin();

  return 0;
}