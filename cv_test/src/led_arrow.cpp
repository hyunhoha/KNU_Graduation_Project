#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <wiringPi.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

#define STRAIGHT_PATH 	"/home/ubuntu/catkin_ws/src/cv_test/images/straight.png" 
#define RIGHT_PATH		"/home/ubuntu/catkin_ws/src/cv_test/images/right.png" 
#define LEFT_PATH		"/home/ubuntu/catkin_ws/src/cv_test/images/left.png" 

#define STOP_PATH		"/home/ubuntu/catkin_ws/src/cv_test/images/straight.png"

// Size of ARROW Image
#define SRC_COL			300
#define SRC_ROW			300

// GPIO LED Pin Setting
#define GREEN			16
#define YELLOW			13
#define RED				12

cv::Mat src_straight;
cv::Mat src_left;
cv::Mat src_right;
cv::Mat src_stop;

cv::Mat src;
cv::Mat src_gray;
cv::Mat frame;

void msgCallback(const geometry_msgs::Twist& msg)
{
	double linear_x = msg.linear.x;
	//double linear_y = msg.linear.y;
	//double linear_z = msg.linear.z;

	//double angular_x = msg.angular.x;
	//double angular_y = msg.angular.y;
	double angular_z = msg.angular.z;

	cv::VideoCapture cap(0);
	cv::Mat src_gray;

	cap >> frame;
			
	// Allocate Value From cmd_vel to direction variable
	if (angular_z == 0.0){
		if(linear_x > 0.0){
			src = src_straight;
			cv::cvtColor(src_straight, src_gray, cv::COLOR_BGR2GRAY);
			digitalWrite(GREEN, HIGH);
			digitalWrite(YELLOW, LOW);
			digitalWrite(RED, LOW);
			ROS_INFO("Go Straight");
		} else {
			src = src_stop;
			cv::cvtColor(src_stop, src_gray, cv::COLOR_BGR2GRAY);	
			digitalWrite(GREEN, LOW);
			digitalWrite(YELLOW, LOW);
			digitalWrite(RED, HIGH);
			ROS_INFO("STOP!");
		}
	}else if (angular_z > 0.0){
		src = src_left;	
		cv::cvtColor(src_left, src_gray, cv::COLOR_BGR2GRAY);	
		digitalWrite(GREEN, LOW);
		digitalWrite(YELLOW, HIGH);
		digitalWrite(RED, LOW);
		ROS_INFO("Go LEFT");
	}else{
		src = src_right;	
		cv::cvtColor(src_right, src_gray, cv::COLOR_BGR2GRAY);	
		digitalWrite(GREEN, LOW);
		digitalWrite(YELLOW, HIGH);
		digitalWrite(RED, LOW);
		ROS_INFO("Go RIGHT");
	}
			
	cv::Mat imageROI(frame, cv::Rect(frame.cols - SRC_COL, frame.rows - SRC_ROW, SRC_COL, SRC_ROW));
	
	cv::Mat mask(src_gray);
	src.copyTo(imageROI, mask);
	cv::imshow("streaming video", frame);
		
	if(cv::waitKey(1) == 27) cv::destroyAllWindows();
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "move_arrow");
	ros::NodeHandle nh;

	// Arrow Image Read
	src_straight = cv::imread(STRAIGHT_PATH);
	src_right = cv::imread(RIGHT_PATH);
	src_left = cv::imread(LEFT_PATH);
	src_stop = cv::imread(STOP_PATH);

	// WiringPi Setup
	wiringPiSetupGpio();
	pinMode(GREEN, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(RED, OUTPUT);

	ros::Subscriber sub = nh.subscribe("/cmd_vel", 1, &msgCallback);
	
	ros::Rate loop_rate(10);
	while (ros::ok()){
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
