#!/usr/bin/env python
import rospy
import tf
import ros
import cv2
from cv_bridge import CvBridge, CvBridgeError
from std_msgs.msg import String
from nav_msgs.msg import Odometry

DIRECTION_PATHS = []
for i in range(10):
    if i==0:
        DIRECTION_PATHS.append("/home/ubuntu/catkin_ws/src/cv_test/images/0.png")
    else:
        strs = "/home/ubuntu/catkin_ws/src/cv_test/images/" + str(i * 10) + ".png"
        strs_ ="/home/ubuntu/catkin_ws/src/cv_test/images/" + str(i * 10) + "_.png"
        DIRECTION_PATHS.append(strs)
        DIRECTION_PATHS.append(strs_) 

# initialize the CVBridge class

cv2.namedWindow("Image Window", cv2.WINDOW_NORMAL)

def callback(odometry):
    global DIRECTION_PATHS
    angle = odometry.twist.twist.angular.z
    angle_transform = angle/3.1415*180
    rospy.loginfo(rospy.get_caller_id() + " angle : %f", angle/3.1415*180)
    # while cv2.waitKey(50) < 0:
    cnt = int(int(angle_transform) / int(10))
    dirs = cv2.imread(DIRECTION_PATHS[cnt], cv2.IMREAD_COLOR)
    cv2.imshow("Image Window", dirs)
    cv2.waitKey(50)

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("/odom", Odometry, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
