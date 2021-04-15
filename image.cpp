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


using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
    Mat img;
    Mat imgNG;
    Mat binary;
    Mat dst, cdst, cdstP;
    int seuil=128;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat comp_conn, img_contours;
    Rect contourRect;
    Mat imgBIN1, kernel;
    
    
    VideoCapture cap("video-example-4.mp4");
    VideoWriter out1, out2;
    char key=0;
    Mat frame;
    Mat test;
    out1.open("flux_orig.avi" , cv::VideoWriter::fourcc('M','J','P','G'), 20.0,Size(640,480),false);
    out2.open("flux_segm.avi" , cv::VideoWriter::fourcc('M','J','P','G'), 20.0,Size(640,480),true);


    while(cap.isOpened())
    {
        cap.read(frame);
        
        Canny(frame, dst, 50, 280, 3);
        cvtColor(dst, cdst, COLOR_GRAY2BGR);
        
        
        cdstP = cdst.clone();
        
        vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
        vector<float> pos, angle;
        
        // Draw the lines
        for( size_t i = 0; i < linesP.size(); i++ )
        {
            Vec4i l = linesP[i];
            line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
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
        auto n_angle = angle.size(); 
        float average_angle = 0.0f;
        if ( n_angle != 0) {
             average_angle = std::accumulate( angle.begin(), angle.end(), 0.0) / n_angle; 
        }
        
        line(cdstP, Point(average_pos, 500), Point(50*sin(average_angle) + average_pos, 50*cos(average_angle) + 500), Scalar(0,255,0), 3, LINE_AA);
        
        imshow("Detected Lines 2", cdstP);

        imshow("flux original", frame);
        //usleep(1000000);
        key= waitKey(1);
        if  (key == 'q')
           break;
    }
}

