#!/usr/bin/env python
import rospy
import tf
import ros
import cv2
from cv_bridge import CvBridge, CvBridgeError
from std_msgs.msg import String
from nav_msgs.msg import Odometry

STRAIGHT_PATH = '/home/ubuntu/catkin_ws/src/cv_test/images/straight.png'
RIGHT_PATH = '/home/ubuntu/catkin_ws/src/cv_test/images/right.png'
LEFT_PATH = '/home/ubuntu/catkin_ws/src/cv_test/images/left.png'
LEFT_ST_PATH = '/home/ubuntu/catkin_ws/src/cv_test/images/left_straight.png'
RIGHT_ST_PATH = '/home/ubuntu/catkin_ws/src/cv_test/images/right_straight.png'

# initialize the CVBridge class
bridge = CvBridge()
straight = cv2.imread(STRAIGHT_PATH, cv2.IMREAD_COLOR)
right = cv2.imread(RIGHT_PATH, cv2.IMREAD_COLOR)
left = cv2.imread(LEFT_PATH, cv2.IMREAD_COLOR)
ls = cv2.imread(LEFT_ST_PATH, cv2.IMREAD_COLOR)
rs = cv2.imread(RIGHT_ST_PATH, cv2.IMREAD_COLOR)
cv2.namedWindow("Image Window", cv2.WINDOW_NORMAL)

def callback(odometry):
    angle = odometry.twist.twist.angular.z
    angle_transform = angle/3.1415*180
    rospy.loginfo(rospy.get_caller_id() + " angle : %f", angle/3.1415*180)
    # while cv2.waitKey(50) < 0:
    if -10 < angle_transform < 10 :
        cv2.imshow("Image Window", straight)
    elif 30 > angle_transform > 10 :
        cv2.imshow("Image Window", ls)
    elif -30 < angle_transform < -10 :
        cv2.imshow("Image Window", rs)
    elif angle_transform > 30 :
        cv2.imshow("Image Window", left)
    elif angle_transform < -30 :
        cv2.imshow("Image Window", right)    
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
