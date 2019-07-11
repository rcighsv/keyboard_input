#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <iostream>
#include <string>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main(int argc, char **argv)
{
    ros::init(argc, argv, "keyboard_input");
    ros::NodeHandle nh;
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);
    ros::Publisher coord_msg_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("keyboard_input/coord_msg", 10);

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 2;
    pose.pose.orientation.x =0;
    pose.pose.orientation.y =0;
    pose.pose.orientation.z =-.99;
    pose.pose.orientation.w =-0.04;
    int c = 0;
    string inStr;
    while(ros::ok())
    {
   	    cin >> inStr;

        if(inStr.compare("w") == 0)
        {
            cout << endl << "Up" << endl;//key up
            pose.pose.position.x -= 1.0;
        }
        else if(inStr.compare("s") == 0)
        {
            cout << endl << "Down" << endl;   // key down
            pose.pose.position.x += 1.0;
        }
        else if(inStr.compare("a") == 0)
        {
            cout << endl << "Left" << endl;  // key left
            pose.pose.position.y -= 1.0;
        }
        else if(inStr.compare("d") == 0)
        {
            cout << endl << "Right" << endl;  // key right
            pose.pose.position.y += 1.0;
        }
        else if(inStr.compare("q") == 0)
        {
            break;
        }

        cout << "inStr =  " << inStr << endl;

        cout << "pose.pose.position.x = " << pose.pose.position.x << endl
             << "pose.pose.position.y = " << pose.pose.position.y << endl << endl;
        //local_pos_pub.publish(pose);
        coord_msg_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
