/*
 * ros1_local_pub.cpp
 *
 *  Created on: May 29, 2018
 *      Author: cj
 */
#include "ros/ros.h"
#include "std_msgs/String.h"
//#include "test_msgs/test_message.h"
#include <iostream>
#include <fstream>
using namespace std;

#include <sys/time.h>

#include "micros_rtt/node_handle.hpp"
#include "micros_rtt/publisher.h"
#include "micros_rtt/topic_manager.h"

long long getCurrentTime()      //直接调用这个函数就行了，返回值最好是int64_t，long long应该也可以
{
   struct timeval tv;
   gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中
   return tv.tv_sec * 1000000 + tv.tv_usec;
}

string anylengthstr(int length)
{
	string str="";
	for(int i=0;i<length;i++)
	{
		str+="A";
	}
	return str;
}

string num_to_str(int n)//整数变字符串
{
    stringstream ss;
    ss<<n;
    return ss.str();
}

/*int str_to_num(string &str)//字符串变整数
{
    int num;
    stringstream ss(str);
    ss>>num;
    return num;
}

int size_handle(string s)
{
	int n;

	string s_num;
    size_t found1=s.find("K");
	if(found1!=string::npos)
	{
		s_num=s.substr(0,found1);
		n=str_to_num(s_num)*1024;
		return n;
	}

	size_t found2=s.find("M");
	if(found2!=string::npos)
	{
		s_num=s.substr(0,found2);
		n=str_to_num(s_num)*1024;
		return n;
	}

	n=str_to_num(s);
	return n;
}*/

int main(int argc, char **argv)
{
	ros::init(argc, argv, "ros1_local_pub");
	//ros::NodeHandle n;
	micros_rtt::NodeHandle n;
	//ros::Publisher pub = n.advertise<std_msgs::String>("message",1000);
	//ros::Publisher pub = n.advertise<test_msgs::test_message>("message",1000);

	micros_rtt::Publisher pub = n.advertise<std_msgs::String>("message",1000);
	//micros_rtt::TopicManager tm;

	ros::Rate loop_rate(10);
	//int count=0;

	const std::string PARAM_NAME = "~msg_size" ;
	int msg_size;
	bool ok = ros::param::get(PARAM_NAME,msg_size);
	if(!ok) {
		ROS_FATAL_STREAM("Could not get parameter msg_size") ;
		exit (1) ;
	}

	string str=anylengthstr(msg_size);
	cout<<"the size of message published is : "<< msg_size <<endl;

	string filename="rtt_local_interprocess_"+num_to_str(msg_size)+"_pub.txt";
    ofstream out(filename.c_str());
    if (!out.is_open())
    {
        cout << "Error opening file";
        exit (1);
    }
	//while(ros::ok())
	for(int count=1;count<=50;count++)
	{
		//count++;
		//string str=num_to_str(count);
		//str+=anylengthstr(4*1024*1024);
		ROS_INFO("pub the %d message.\n",count);
		std_msgs::String msg;
		msg.data =str ;
		//test_msgs::test_message msg;
		//msg.msg_num=count;
		//msg.msg_data=str;
		//ROS_INFO("%s",msg.msg_data.c_str());
		long long t = getCurrentTime();
		pub.publish(msg);
		out << count <<" "<<t<<endl;
		//ros::spinOnce();
		loop_rate.sleep();
	}
	out.close();

	return 0;
}




