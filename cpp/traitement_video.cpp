#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video.hpp"
// #include "videoio.hpp"
#include <math.h>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <unistd.h>
#include <numeric>
#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "tf/tf.h"
#include <cstdlib>
#include "std_msgs.h"
#include "sensor_msgs.h"

using namespace cv;
using namespace std;

uint8[] img_saved;

void cam(const sensor_msgs::Image::ConstPtr& image)
{
    img_saved = image->data;
}


int main(int argc, char *argv[])
{
    ros::init(argc,argv,"traitement_video");
    ros::NodeHandle n;
    ros::Subscriber cam_sub = n.subscribe("raspicam",1000,cam);

    ros::Publisher position_ligne = n.advertise<std_msgs::Float64MultiArray>("position_ligne",1000);
    ros::Rate loop_rate(25);
    while(ros::ok())
    {	
        position_ligne.publish(image_processing(img_saved));
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}


std_msgs::Float64MultiArray image_processing(uint8[] image)
{
    Mat dst, cdstP;    
    Mat frame;
    const unsigned int data_sz = 2;
    std_msgs::Float64MultiArray m;
    m.layout.dim.push_back(std_msgs::MultiArrayDimension());
    m.layout.dim[0].size = data_sz;


    frame = imread(image);
    
    Canny(frame, dst, 50, 280, 3);
    cvtColor(dst, cdstP, COLOR_GRAY2BGR);
    
    
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
    vector<float> pos, angle;
    
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        //line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        pos.push_back(0.5*(l[0] + l[2]));
        
        if (l[3] == l[1])
            angle.push_back(CV_PI/2);
        else            
            angle.push_back(atan(float(abs(l[2] - l[0]))/float(abs(l[3] - l[1]))));
    }
    

    auto n_pos = pos.size(); 
    float average_pos = 0.0f;
    if ( n_pos != 0) {
         average_pos = std::accumulate( pos.begin(), pos.end(), 0.0) / n_pos; 
    }
    m.data[0] = average_pos;
    auto n_angle = angle.size(); 
    float average_angle = 0.0f;
    if ( n_angle != 0) {
         average_angle = std::accumulate( angle.begin(), angle.end(), 0.0) / n_angle; 
    }
    m.data[1] = average_angle;
    
    //line(cdstP, Point(average_pos, 500), Point(50*sin(average_angle) + average_pos, 50*cos(average_angle) + 500), Scalar(0,255,0), 3, LINE_AA);
    
    //imshow("Detected Lines", cdstP);

    //imshow("flux original", frame);
    return m;
    
}
