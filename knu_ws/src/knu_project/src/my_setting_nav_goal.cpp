#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <termios.h>
#include "std_msgs/String.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

char getch()
{
    fd_set set;
    struct timeval timeout;
    int rv;
    char buff = 0;
    int len = 1;
    int filedesc = 0;
    FD_ZERO(&set);
    FD_SET(filedesc, &set);
     
    timeout.tv_sec = 0;
    timeout.tv_usec = 1000;
 
    rv = select(filedesc + 1, &set, NULL, NULL, &timeout);
 
    struct termios old = {0};
    if (tcgetattr(filedesc, &old) < 0)
        ROS_ERROR("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(filedesc, TCSANOW, &old) < 0)
        ROS_ERROR("tcsetattr ICANON");
 
    if(rv == -1)
        ROS_ERROR("select");
    else if(rv == 0)
        ROS_INFO("no_key_pressed");
    else
        read(filedesc, &buff, len );
 
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
        ROS_ERROR ("tcsetattr ~ICANON");
    return (buff);
}


int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;

  // ros::Subscriber qr_code_1;
  // qr_code_1 = n.subscribe("/visp_auto_tracker/code_message", 10, qr_code_goal_1);
  // visp_auto_tracker = ROS에서 qr code 인식할 수 있도록 한 메시지.

  ros::Rate loop_rate(10);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }


  while (ros::ok())
  {
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    int c = getch();

    if (c == '1') // 1테이
      {
      //we'll send a goal to the robot to move 1 meter forward
      goal.target_pose.pose.position.x = 2.8;
      goal.target_pose.pose.position.y = 4.0;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("Table 1 reached !");
      ac.sendGoal(goal);
      ac.waitForResult();
      }
    else if (c == '2')
      {
      //we'll send a goal to the robot to move 1 meter forward
      goal.target_pose.pose.position.x = 0.2;
      goal.target_pose.pose.position.y = 4.0;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("Table 2 reached !");
      ac.sendGoal(goal);
      ac.waitForResult();
      }

    else if (c=='3')
      {
      //we'll send a goal to the robot to move 1 meter forward
      goal.target_pose.pose.position.x = -2.5;
      goal.target_pose.pose.position.y = 4.0;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("Table 3 reached !");
      ac.sendGoal(goal);
      ac.waitForResult();
      }
  
    else if (c=='4')
      {
      //we'll send a goal to the robot to move 1 meter forward
      goal.target_pose.pose.position.x = 3.;
      goal.target_pose.pose.position.y = 1.4;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("Table 4 reached !");
      ac.sendGoal(goal);
      ac.waitForResult();
      }

    else if (c=='5')
      {
      //we'll send a goal to the robot to move 1 meter forward
      // goal.target_pose.pose.position.x = 0.0;
      // goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.position.x = .2;
      goal.target_pose.pose.position.y = 1.5;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("HOME reached !");
      ac.sendGoal(goal);
      ac.waitForResult();
      }

    else if (c=='6')
      {
      //we'll send a goal to the robot to move 1 meter forward
      // goal.target_pose.pose.position.x = 0.0;
      // goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.position.x = -2.5;
      goal.target_pose.pose.position.y = 1.5;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("HOME reached !");
      ac.sendGoal(goal);
      ac.waitForResult();
      }

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base moved 1 meter forward");
    else
      ROS_INFO("The base failed to move forward 1 meter for some reason");

    ROS_INFO("%c", c);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
