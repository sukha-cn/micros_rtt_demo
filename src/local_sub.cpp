/*
 * ros1_local_sub.cpp
 *
 *  Created on: May 29, 2018
 *      Author: cj
 */
#include "ros/ros.h"
#include "std_msgs/String.h"
//#include "test_msgs/test_message.h"
#include <fstream>
#include <sys/time.h>
using namespace std;

#include "micros_rtt/node_handle.hpp"
#include "micros_rtt/subscriber.h"

ofstream outfile;

long long getCurrentTime()      //直接调用这个函数就行了，返回值最好是int64_t，long long应该也可以
{
   struct timeval tv;
   gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中
   return tv.tv_sec * 1000000 + tv.tv_usec;
}

string num_to_str(int n)//整数变字符串
{
    stringstream ss;
    ss<<n;
    return ss.str();
}

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	long long t = getCurrentTime();
	//int pos=str.find('A');
	//str=str.substr(0,pos);
	//int num=msg->data;
	//ROS_INFO("I heard: [%d]", num);

	std::string str=msg->data;
	//ROS_INFO("I heard: [%s]", str.c_str());

	string filename="rtt_local_interprocess_"+num_to_str(str.size())+"_sub.txt";
	if(!outfile.is_open ())
		outfile.open(filename.c_str(), ios::out);

//    outfile<<num<<" "<<t<<endl;
//    if(num==50)
//    {
//    	outfile.close();
//    	exit (1);
//    }

}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "ros1_local_sub");
	//ros::NodeHandle n;

	micros_rtt::NodeHandle n;
	ROS_INFO("begin to sub.\n");
	//ros::Subscriber sub= n.subscribe("message", 1000, chatterCallback);

	//micros_rtt::Subscriber sub= n.subscribe("message", 1000, chatterCallback);
	ros::spin();

	return 0;
}




