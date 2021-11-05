#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <termios.h>
#include "std_msgs/String.h"
#include <chrono>
#include <bits/stdc++.h>
#include "nav_msgs/Odometry.h"
#include <vector>
#include "geometry_msgs/Twist.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace std;

struct goal_pos
{
  goal_pos(int a, int b, int c) : x{a}, y{b}, w{c} {};
  int x;
  int y;
  int w;
};

struct pos
{
  pos(float a, float b, float c) : x{a}, y{b}, w{c} {};
  float x;
  float y;
  float w;
};

move_base_msgs::MoveBaseGoal goal;
vector<goal_pos> goals;
pos state(0.0, 0.0, 0.0);
ros::Subscriber sub; 
