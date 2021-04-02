#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv)
{
	ros::init(argc,argv,"controleur");
	ros::NodeHandle n;

    // Subscriber: 
	ros::Subscriber pos_ligne_sub   = n.subscribe("position_ligne",1000,recupconsigne);
    ros::Subscriber angl_roues_sub  = n.subscribe("angle_roues",1000,recupconsigne);
    ros::Subscriber vitesse_mot_sub = n.subscribe("vitesse_moteur",1000,recupconsigne);

    // Publisher: 
	ros::Publisher cons_pub = n.advertise<std_msgs::Float64>("consigne",1000);

	ros::Rate loop_rate(25);

	while(ros::ok())
	{	
        ros::spinOnce();
		loop_rate.sleep();
    }

    return 0;
}