#!/usr/bin/env python
import rospy
import tf
import ros
from std_msgs.msg import String
from nav_msgs.msg import Path

def callback(path):
    quaternion = (
            path.poses[-1].pose.orientation.x,
            path.poses[-1].pose.orientation.y,
            path.poses[-1].pose.orientation.z,
            path.poses[-1].pose.orientation.w
            )
    euler = tf.transformations.euler_from_quaternion(quaternion)
    rospy.loginfo(rospy.get_caller_id() + " yaw : %f", euler[2]/3.1415*180)
    
def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("/move_base/DWAPlannerROS/global_plan", Path, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
