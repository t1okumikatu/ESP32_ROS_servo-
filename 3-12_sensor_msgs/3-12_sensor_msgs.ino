#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

ros::NodeHandle nh;

std_msgs::Float64 angle_msg;
ros::Publisher chatter("chatter",&angle_msg);

void messageCb( const sensor_msgs::JointState& msg){
  angle_msg.data = msg.position[0]*180/3.14;
}

ros::Subscriber<sensor_msgs::JointState> sub("joint_states", messageCb );

void setup()
{ 
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{  
  chatter.publish(&angle_msg);
  nh.spinOnce();
  delay(100);
}
