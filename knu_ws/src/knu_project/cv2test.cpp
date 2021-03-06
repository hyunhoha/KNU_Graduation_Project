#include <iostream>
#include <opencv2/opencv.hpp>
 
int main()
{
    std::cout << "OpenCV Version : " << CV_VERSION << std::endl;
    cv::Mat img;
    cv::namedWindow("EXAMPLE01", CV_WINDOW_AUTOSIZE);
 
    img = cv::imread("cat.jpg", CV_LOAD_IMAGE_COLOR);
    if (img.empty())
    {
        std::cout << "[!] You can NOT see the cat!" << std::endl;
        return -1;
    }
    cv::imshow("EXAMPLE01", img);
    cv::waitKey(0);
    cv::destroyWindow("EXAMPLE01");
    return 0;
}
 


// 출처: https://ledgku.tistory.com/59 [블로그]