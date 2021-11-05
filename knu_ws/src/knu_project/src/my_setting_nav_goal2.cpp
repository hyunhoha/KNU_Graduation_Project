#include "my_setting_nav_goal2.h"
#include <unistd.h>

using namespace std;

// Insert the code that will be timed

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
  cout << "input" << endl;
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

  if (rv == -1)
    ROS_ERROR("select");
  else if (rv == 0)
    ROS_INFO("no_key_pressed");
  else
    read(filedesc, &buff, len);

  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
    ROS_ERROR("tcsetattr ~ICANON");
  return (buff);
}

bool get_chf()
{

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  int c = getch() - '0' - 1;
  if (c < 0 || c > 5)
    return false;

  goal.target_pose.pose.position.x = goals[c].x;
  goal.target_pose.pose.position.y = goals[c].y;
  goal.target_pose.pose.orientation.w = goals[c].w;
  return true;
}

void odom_cb(const nav_msgs::Odometry &Odom)
{
  // ROS_INFO("I heard: [%d]", Odom->pose.pose.position.x);
  // ROS_INFO("I heard Odom");
  state.x = Odom.pose.pose.position.x;
  state.y = Odom.pose.pose.position.y;
  // state.w = 1;  

  auto q = Odom.pose.pose.orientation;
  state.w = atan2(2 * (q.w * q.z + q.y * q.x), 1 - 2 * (q.y * q.y + q.z * q.z));

  // cout << "state : " << state.x << " " << state.y << " " << state.w << "\n";

  //  public static Vector3 QuaternionToEuler_new(Quaternion q)
  //       {
  //           //This is the code from 
  //           //http://www.mawsoft.com/blog/?p=197
  //           var rotation = q;
  //           double q0 = rotation.W;
  //           double q1 = rotation.Y;
  //           double q2 = rotation.X;
  //           double q3 = rotation.Z;

  //           Vector3 radAngles = new Vector3();
  //           radAngles.Y = (float)Math.Atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (Math.Pow(q1, 2) + Math.Pow(q2, 2)));
  //           radAngles.X = (float)Math.Asin(2 * (q0 * q2 - q3 * q1));
  //           radAngles.Z = (float)Math.Atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (Math.Pow(q2, 2) + Math.Pow(q3, 2)));

  //           return radAngles;
  //       }




  // state.x = Odom-
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;

  sub = n.subscribe("odom", 1, &odom_cb);
  // pub = n.publisher
  ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  goals.emplace_back(2.7, 1.5, 1.0);
  goals.emplace_back(0.2, 4.0, 1.0);
  goals.emplace_back(-2.5, 4.0, 1.0);
  goals.emplace_back(3, 1.4, 1.0);
  goals.emplace_back(0.2, 1.5, 1.0);
  goals.emplace_back(-2.5, 1.5, 1.0);

  auto start = chrono::steady_clock::now();

  // ros::Subscriber qr_code_1;
  // qr_code_1 = n.subscribe("/visp_auto_tracker/code_message", 10, qr_code_goal_1);
  // visp_auto_tracker = ROS에서 qr code 인식할 수 있도록 한 메시지.

  ros::Rate loop_rate(30);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  while (ros::ok())
  {
    bool flag = get_chf();
    if (flag)
    {

      ROS_INFO("Searching..");

  //     goal.target_pose.pose.position.x = goals[c].x;
  // goal.target_pose.pose.position.y = goals[c].y;
    geometry_msgs::Twist tw;
    tw.angular.z = 0.5;
    cmd_pub.publish(tw);

    // cout << "goal ang : " << atan2(goal.target_pose.pose.position.y - state.y, goal.target_pose.pose.position.x - state.x) << " "
    // << "state ang : " << state.w << "\n";
      // while (abs(atan2(goal.target_pose.pose.position.y - state.y, goal.target_pose.pose.position.x - state.x) - state.w) > 0.4)
      auto goal_ang = atan2(goal.target_pose.pose.position.y - state.y, goal.target_pose.pose.position.x - state.x);
      while(1)
      {
        // cmd_pub.publish(tw);
        // cout << "ang : " <<  goal_ang << " " << state.w << "\n";
        if (abs( goal_ang- state.w) <= 0.2) break;
        loop_rate.sleep();
        ros::spinOnce();
      }

      tw.angular.z = 0;
      cmd_pub.publish(tw);

      usleep(500);
      
      
      ac.sendGoal(goal);
      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the base moved 1 meter forward");
      else
        ROS_INFO("The base failed to move forward 1 meter for some reason");
    }
    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
