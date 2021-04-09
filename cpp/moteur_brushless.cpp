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

void mouvement_moteur()
{
}

float vitesse_moteur()
{
    float vitesse;
    vitesse = ;

    return vitesse;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "moteur_brushless");
    ros::NodeHandle n;

    // Subscriber:
    ros::Subscriber commande = n.subscribe("commande_vitesse", 1000, get_commande);

    // Publisher:
    ros::Publisher vitesse = n.advertise<std_msgs::Float64>("vitesse_moteur", 1000);

    ros::Rate loop_rate(25);

    while (ros::ok())
    {
        std_msgs::Float64 msg;
        mouvement_moteur();
        msg = vitesse_moteur();
        vitesse.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}