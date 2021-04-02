#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include <cmath>
#include "geometry_msgs/PoseStamped.h"
#include "tf/tf.h"
#include <cstdlib>
#include "std_msgs/Float64.h"
float cons1;
float cons2;
float cons3;

void recupconsigne(const geometry_msgs::Pose2D::ConstPtr& msg)
{
	cons1 = msg->Pose.x;
	cons2 = msg->Pose.y;
	cons3 = msg->Pose.theta;
}

float control_servo()
{  float control

	return control
}
float control_brush()
{  float control

	return control
}
int main(int argc, char **argv)
{
	ros::init(argc,argv,"controleur");
	ros::NodeHandle n;
	ros::Subscriber subcons = n.subscribe("consigne",1000,recupconsigne);
	ros::Publisher brush_pub = n.advertise<std_msgs::Float64>("commande_direction",1000);
	ros::Publisher servo_pub = n.advertise<std_msgs::Float64>("commande_vitesse",1000);
	ros::Rate loop_rate(25);
	while(ros::ok())
	{	std_msgs::Float64 msgbrush;
		std_msgs::Float64 msgservo;
		msgservo.data = control_servo();
		msgbrush.data = control_brush();
		brush_pub.publish(msgbrush);
		servo_pub.publish(msgservo);
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}