#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>


int main(int argc, char** argv){
	cv::VideoCapture vcap;
	cv::Mat image;
	cv_bridge::CvImage img_bridge;
	sensor_msgs::Image img_msg;

	//const std::string address = "http://root:drrobot@192.168.0.65:8081/mjpg/video.mjpg";

	ros::init(argc, argv, "ip_camera_node");
	ros::NodeHandle n;

	std::string published_image_topic = "";
	std::string username = "";
	std::string password = "";
	std::string url = "";

	n.param("ip_camera_node/topic", published_image_topic, std::string("ip_camera_node/image"));
	n.param("ip_camera_node/username", username, std::string("root"));
	n.param("ip_camera_node/password", password, std::string("root"));
	n.param("ip_camera_node/url", url, std::string("localhost:8081/mjpg/video.mjpg"));

	std::string address = "http://" + username + ":" + password + "@" + url;

	ros::Publisher image_publisher = n.advertise<sensor_msgs::Image>(published_image_topic, 100);

	if(!vcap.open(address)){
		ROS_ERROR("Could not open IP camera!");
	}
	int counter = 0;
	while(ros::ok){
		if(vcap.read(image)){
			std_msgs::Header header;
			header.seq = counter;
			header.stamp = ros::Time::now();
			img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, image);
			img_bridge.toImageMsg(img_msg);
			image_publisher.publish(img_msg);
			counter++;
		}
		ros::spinOnce();
	}
	return 0;
}