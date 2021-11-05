// For Test : Draw Straight Arrow on the Cam Video
#include <ros/ros.h>
#include <wiringPi.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

#define STRAIGHT_PATH 	"/home/ubuntu/catkin_ws/src/cv_test/images/straight.png" 
#define RIGHT_PATH		"/home/ubuntu/catkin_ws/src/cv_test/images/right.png" 
#define LEFT_PATH		"/home/ubuntu/catkin_ws/src/cv_test/images/left.png" 

int main(int argc, char** argv){
	ros::init(argc, argv, "push_arrow");

	cv::VideoCapture cap(0);
	cv::Mat frame;
	cv::Mat src = cv::imread(STRAIGHT_PATH);	
	cv::Mat src_gray = cv::imread(STRAIGHT_PATH, CV_LOAD_IMAGE_GRAYSCALE);	


	if(cap.isOpened()){
		while(1){
			cap >> frame;
			cv::Mat imageROI(frame, cv::Rect(frame.cols - src.cols, frame.rows - src.rows, src.cols, src.rows));
			//std::cout << "src "<< src.rows << "   " << src.cols << std::endl;
			//std::cout << "frame " << frame.rows << "   " << frame.cols << std::endl;
			cv::Mat mask(src_gray);
			src.copyTo(imageROI, mask);

			cv::imshow("streaming video", frame);
			if(cv::waitKey(1) == 27) break;
		}
	}

	else{
		std::cout << "NO FRAME, CHECK YOUR CAMERA!" << std::endl;
	}

	cv::destroyAllWindows();

	return 0;
}
