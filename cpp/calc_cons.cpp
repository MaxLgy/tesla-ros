#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include <cmath>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "tf/tf.h"
#include <cstdlib>
#include "std_msgs/Float64.h"

float theta_ligne = 0;
float angle_roue = 0;
float speed_motor = 0;
float speed_motor_max = 2000;
float k = 2;
void getposligne(const std_msgs::Float64::ConstPtr& msg)
{
	theta_ligne = msg->data;
}

void getwheelangle(const std_msgs::Float64::ConstPtr& msg)
{
   angle_roue = msg->data;
}

void getmotorspeed(const std_msgs::Float64::ConstPtr& msg) 
{
	speed_motor = msg->data;
}

float consangle()
{
	float thetad;
	thetad = theta_ligne;
	return thetad;


}

float consspeed()
{
	float speed_motor;

	speed_motor = speed_motor_max - k * theta_ligne;
	return speed_motor;
}
int main(int argc, char **argv)
{
	ros::init(argc,argv,"consigne");
	ros::NodeHandle n;

    // Subscriber: 
	ros::Subscriber pos_ligne_sub   = n.subscribe("position_ligne",1000,getposligne);
    ros::Subscriber angl_roues_sub  = n.subscribe("angle_roues",1000,getwheelangle);
    ros::Subscriber vitesse_mot_sub = n.subscribe("vitesse_moteur",1000,getmotorspeed);

    // Publisher: 
	ros::Publisher cons_pub = n.advertise<geometry_msgs::Pose2D>("consigne",1000);

	ros::Rate loop_rate(25);

	while(ros::ok())
	{	
		geometry_msgs::Pose2D msg;
		msg.x = consspeed();
		std::cout<<"send speed "<<msg.x<<std::endl;
		msg.y = consangle();
		cons_pub.publish(msg);
        ros::spinOnce();
		loop_rate.sleep();
    }

    return 0;
}