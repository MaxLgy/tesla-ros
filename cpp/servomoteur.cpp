#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include <cmath>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "tf/tf.h"
#include <cstdlib>
#include "std_msgs/Float64.h"

float commande;

void get_commande(const std_msgs::Float64::ConstPtr &msg)
{
    commande = msg->data;
}

void mouvement_servo()
{
}

float angle_roues()
{
    float angle;
    angle = ;

    return angle;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "servomoteur");
    ros::NodeHandle n;

    // Subscriber:
    ros::Subscriber commande = n.subscribe("commande_direction", 1000, get_commande);

    // Publisher:
    ros::Publisher angle = n.advertise<std_msgs::Float64>("angle_roues", 1000);

    ros::Rate loop_rate(25);

    while (ros::ok())
    {
        std_msgs::Float64 msg;
        mouvement_servo();
        msg = angle_roues();
        angle.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}