#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

#include "timesync/stringWithTimeStamped.h"

#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace sensor_msgs;
using namespace message_filters;

void callback(const timesync::stringWithTimeStamped::ConstPtr& msg1,const timesync::stringWithTimeStamped::ConstPtr& msg2)
{
  std::cout  << "[Callback receive]" << std::endl;
  std::cout << msg1->payload << std::endl;
  std::cout << msg2->payload << std::endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "receiver");

  ros::NodeHandle nh;

  message_filters::Subscriber<timesync::stringWithTimeStamped> chat1sub(nh, "chat1", 1);
  message_filters::Subscriber<timesync::stringWithTimeStamped> chat2sub(nh, "chat2", 1);
  // TimeSynchronizer<timesync::stringWithTimeStamped, timesync::stringWithTimeStamped > sync(chat1sub, chat2sub, 10);
  // sync.registerCallback(boost::bind(&callback, _1, _2));

  typedef sync_policies::ApproximateTime<timesync::stringWithTimeStamped , timesync::stringWithTimeStamped > MySyncPolicy;

  Synchronizer<MySyncPolicy> sync(MySyncPolicy(20),chat1sub,chat2sub);
  sync.registerCallback(boost::bind(&callback, _1, _2));


  ros::spin();

  return 0;
}
