#!/usr/bin/env python
import RPi.GPIO as GPIO
from time import sleep
import rospy
import ros
import tf
from sensor_msgs.msg import Imu

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)
GPIO.setup(10, GPIO.OUT)

p = GPIO.PWM(12, 50)
q = GPIO.PWM(10, 50)
 
p.start(0)
q.start(0)

angle_y = 0

def callback(imu):
    global angle_y

    quaternion = (
            imu.orientation.x,
            imu.orientation.y,
            imu.orientation.z,
            imu.orientation.w
            )
    euler = tf.transformations.euler_from_quaternion(quaternion)

    # rospy.loginfo(rospy.get_caller_id() + "[%f, %f, %f]", euler[0]/3.141592*180, euler[1]/3.141592*180+8, euler[2]/3.141592*180)
    new_euler = round(euler[1], 1)
    new_ang = (new_euler/3.141592*180+8)/20+7
    if angle_y == 0:
	angle_y = new_ang
    else:
	angle_y = (angle_y*49 + new_ang)/50
	# angle_y = (euler[1]/3.141592*180+8)/20+7
    p.ChangeDutyCycle(angle_y)
    q.ChangeDutyCycle(angle_y)

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("/imu", Imu, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()

p.stop()
q.stop()

GPIO.cleanup()
