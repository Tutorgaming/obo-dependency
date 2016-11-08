/******************************
 *  ROS Node
 *   To create message
 *******************************/

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "timesync/stringWithTimeStamped.h"
#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker1");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<timesync::stringWithTimeStamped>("chat1", 1000);
  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    timesync::stringWithTimeStamped msg;

    std::stringstream ss;
    ss << "[TALKER-1]" << count;

    msg.payload = ss.str();

    msg.header.stamp = ros::Time::now();

    ROS_INFO("%s", msg.payload.c_str());
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
