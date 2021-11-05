// #!/usr/bin/python3

// import rospy
// import tf
// import ros
// import cv2
// from cv_bridge import CvBridge, CvBridgeError
// from std_msgs.msg import String
// from nav_msgs.msg import Odometry, Path
// import tf as tft
// import math

// # bridge = CvBridge()

// cur_state = [0, 0, 0]

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

string DIRECTION_PATHS[20]; // = new string[20];
// for i in range(10):

string base_path = "/home/hyun/knu_ws/src/knu_project/images/";

int main()
{
    for (int i=0; i<10; i++)
    {
        if (i==0)
        {
            // DIRECTION_PATHS[0] = "/home/hyun/knu_ws/src/knu_project/images/0.png";
            DIRECTION_PATHS[0] = base_path + "0.png";
        }
        else
        {
            string tmp = base_path + to_string(i * 10) + ".png";
            string tmp_ = base_path + to_string(i * 10) + "_.png";
            DIRECTION_PATHS[i] = tmp;
            DIRECTION_PATHS[10+i] = tmp_;
        }
    }
}

// for i in range(10):
//     strs_ ="/home/hyun/knu_ws/src/knu_project/images/" + str((i+1) * 10) + "_.png"
//     DIRECTION_PATHS.append(strs_)
// # initialize the CVBridge class

# cv2.namedWindow("Image Window", cv2.WINDOW_NORMAL)

def callback(odometry):
    global cur_state
    global DIRECTION_PATHS
    cur_state[0] = odometry.pose.pose.position.x
    cur_state[1] = odometry.pose.pose.position.y
    angle = odometry.pose.pose.orientation
    cur_state[2] = tft.transformations.euler_from_quaternion([angle.x, angle.y, angle.z, angle.w])[2]

def callback2(local_plan):
    global DIRECTION_PATHS
    global cur_pos

    new_plan = local_plan.poses[-1].pose.position
    new_x = new_plan.x
    new_y = new_plan.y

    heading_ang = (math.atan2(new_y-cur_state[1], new_x-cur_state[0]) - cur_state[2])/3.1415*180
    if heading_ang < -180:
        heading_ang += 360
    heading_ang *= 3
    rospy.loginfo(rospy.get_caller_id() + " angle : %f", heading_ang)
    cnt = int(heading_ang/10)
    if cnt < 0:
        cnt = 10 + abs(cnt)

    dirs = cv2.imread(DIRECTION_PATHS[cnt], cv2.IMREAD_COLOR)
    cv2.imshow("Image Window", dirs)
    cv2.waitKey(50)

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('odom_listener', anonymous=True)

    rospy.Subscriber("/odom", Odometry, callback)
    rospy.Subscriber("/move_base/DWAPlannerROS/local_plan", Path, callback2)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    
    listener()
