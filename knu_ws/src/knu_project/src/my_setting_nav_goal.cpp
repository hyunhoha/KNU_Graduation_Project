#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <termios.h>
#include "std_msgs/String.h"
#include <chrono>
#include <bits/stdc++.h>
#include "nav_msgs/Odometry.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace std;

// Insert the code that will be timed

vector<goal_pos> goals;

goals.emplace_back(2.7, 1.5, 1.0);
goals.emplace_back(0.2, 4.0, 1.0);
goals.emplace_back(-2.5, 4.0, 1.0);
goals.emplace_back(3, 1.4, 1.0);
goals.emplace_back(0.2, 1.5, 1.0);
goals.emplace_back(-2.5, 1.5, 1.0);

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

struct goal_pos
{
  goal_pos (int a, int b, int c ) x{a}, y{b}, w{c} {};
  int x;
  int y;
  int w;
};


void odom_cb(const nav_msgs::Odometry &Odom)
{
  // ROS_INFO("I heard: [%d]", Odom->pose.pose.position.x);
  ROS_INFO("I heard Odom");
}

move_base_msgs::MoveBaseGoal goal;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("odom", 1000, &odom_cb);

  auto start = chrono::steady_clock::now();

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

  get_chf();
  // odoms();
  ros::spin();

  void get_chf()
  {
    
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    int c = getch()-'0'-1;
    if (c<0 || c>5) continue;

    goal.target_pose.pose.position.x = goals[c].x;
    goal.target_pose.pose.position.y = goals[c].y;
    goal.target_pose.pose.position.w = goals[c].w;

    // ROS_INFO("Table ", i+1 , "Reached!");
    ROS_INFO("Searching..");
    ac.sendGoal(goal);
    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base moved 1 meter forward");
    else
      ROS_INFO("The base failed to move forward 1 meter for some reason");

    // ROS_INFO("%c", c);

    ros::spinOnce();

    loop_rate.sleep();
  }

  

  while (ros::ok())
  {
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();


    int c = getch()-'0'-1;
    if (c<0 || c>5) continue;

    goal.target_pose.pose.position.x = goals[c].x;
    goal.target_pose.pose.position.y = goals[c].y;
    goal.target_pose.pose.position.w = goals[c].w;

    // ROS_INFO("Table ", i+1 , "Reached!");
    ROS_INFO("Searching..");
    ac.sendGoal(goal);
    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base moved 1 meter forward");
    else
      ROS_INFO("The base failed to move forward 1 meter for some reason");

    // ROS_INFO("%c", c);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
