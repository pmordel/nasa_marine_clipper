#include <iostream> 
#include <string> 
#include <sstream> 

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <nmea_msgs/Sentence.h>
#include <nasa_marine_clipper/Anemometer.h>


using namespace std;
nasa_marine_clipper::Anemometer a;


void nmea_callback(const nmea_msgs::Sentence::ConstPtr& msg){
    ROS_INFO("Anemometer NMEA 0183 data sentence: [%s]", msg->sentence.c_str());
    stringstream ss(msg->sentence);
    string tmp;
    vector<string> s;
    while(getline(ss,tmp,',')){
    	s.push_back(tmp);
    }
    a.header=msg->header;
    a.wind_angle=strtof((s[1]).c_str(),0);
    a.reference=s[2];
    a.wind_speed=strtof((s[3]).c_str(),0);
    a.speed_unit=s[4];
    a.status=s[5];
}

int main (int argc, char** argv){
    ros::init(argc, argv, "nasa_marine_clipper_node");
    ros::NodeHandle nh;

    ros::Subscriber nmea_sentence_sub = nh.subscribe("/nmea_sentence", 1000, nmea_callback);
    ros::Publisher anemometer_pub = nh.advertise<nasa_marine_clipper::Anemometer>("/nasa_marine_clipper/anemometer", 1000);

    ros::Rate loop_rate(10);

    while(ros::ok()){

        ros::spinOnce();
        anemometer_pub.publish(a);
	loop_rate.sleep();

    }
}

