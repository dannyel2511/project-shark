#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <cmath>

const double PI = atan(1)*4;

using namespace ros;

void stop(Publisher &chatter_pub, Rate &loop_rate, geometry_msgs::Twist &msg) {
   msg.linear.x = 0.0;
   msg.angular.z = 0.0;
   chatter_pub.publish(msg);
}

void go_forward(Publisher &chatter_pub, Rate &loop_rate, geometry_msgs::Twist &msg) {
   msg.linear.x = 0.5;
   msg.angular.z = 0.0;
   for(int i = 0; i < 5; i++) {
      chatter_pub.publish(msg);
      loop_rate.sleep();
   }
}
void go_backward(Publisher &chatter_pub, Rate &loop_rate, geometry_msgs::Twist &msg) {
   msg.linear.x = -0.5;
   msg.angular.z = 0.0;
   for(int i = 0; i < 5; i++) {
      chatter_pub.publish(msg);
      loop_rate.sleep();
   }
}
void turn_right(Publisher &chatter_pub, Rate &loop_rate, geometry_msgs::Twist &msg) {
   for(int i = 0; i < 2; i++) {
      msg.linear.x = 0.0;
      msg.angular.z = -PI/2.0;
      chatter_pub.publish(msg);
      loop_rate.sleep();
      stop(chatter_pub, loop_rate, msg);
   }
}
void turn_left(Publisher &chatter_pub, Rate &loop_rate, geometry_msgs::Twist &msg) {
   for(int i = 0; i < 2; i++) {
      msg.linear.x = 0.0;
      msg.angular.z = PI/2.0;
      chatter_pub.publish(msg);
      loop_rate.sleep();
      stop(chatter_pub, loop_rate, msg);
   }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "dannyel_talker");

  NodeHandle n;

  Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  Rate loop_rate(1);

  geometry_msgs::Twist msg;

  while (ros::ok())
  {
    go_forward(chatter_pub, loop_rate, msg);
    stop(chatter_pub, loop_rate, msg);
    loop_rate.sleep();

    go_backward(chatter_pub, loop_rate, msg);
    stop(chatter_pub, loop_rate, msg);
    loop_rate.sleep();

    turn_right(chatter_pub, loop_rate, msg);
    stop(chatter_pub, loop_rate, msg);
    loop_rate.sleep();

    turn_left(chatter_pub, loop_rate, msg);
    stop(chatter_pub, loop_rate, msg);
    loop_rate.sleep();

    ros::spinOnce();
    //loop_rate.sleep();
  }


  return 0;
}