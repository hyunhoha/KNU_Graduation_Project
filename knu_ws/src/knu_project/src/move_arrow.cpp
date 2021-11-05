#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
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

cv::Mat src_straight;
cv::Mat src_left;
cv::Mat src_right;
cv::Mat src_stop;

cv::Mat src;
cv::Mat src_gray;
cv::Mat frame;

void msgCallback(const geometry_msgs::Quaternion& msg)
{
	//double position_z = msg.position.z;

	double orientation_w = msg.w;

	cv::Mat src_gray;

	// Allocate Value From cmd_vel to direction variable
	if (orientation_w >= 0.0){
			// cv::cvtColor(src_straight, src_gray, cv::COLOR_BGR2GRAY);
			ROS_INFO("Go LEFT");
	}else{
		src = src_right;	
		cv::cvtColor(src_right, src_gray, cv::COLOR_BGR2GRAY);	
		ROS_INFO("Go RIGHT");
	}
			
	//cv::Mat imageROI(frame, cv::Rect(frame.cols - SRC_COL, frame.rows - SRC_ROW, SRC_COL, SRC_ROW));
	
	//cv::Mat mask(src_gray);
	//src.copyTo(imageROI, mask);
	//cv::imshow("streaming video", frame);
		
	//if(cv::waitKey(1) == 27) cv::destroyAllWindows();
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "move_arrow");
	ros::NodeHandle nh;

//	src_straight = cv::imread(STRAIGHT_PATH);
//	src_right = cv::imread(RIGHT_PATH);
//	src_left = cv::imread(LEFT_PATH);
//	src_stop = cv::imread(STOP_PATH);

	ros::Subscriber sub = nh.subscribe("/move_base/DWAPlannerROS/local_plan", 1, &msgCallback);
	
	ros::Rate loop_rate(10);
	while (ros::ok()){
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
