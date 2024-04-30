// Include files for required libraries
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv_aee.hpp"

using namespace cv;
using namespace std;

int main(){
    int lowH_red = 0, highH_red = 9, lowH_blue = 90, highH_blue = 128, lowH_green = 36, highH_green = 89, lowS_red = 50, lowS_blue = 150, lowS_green = 70, lowV_red = 50, lowV_blue = 150, lowV_green = 60, highS = 255, highV = 255, redCount, blueCount, greenCount;    // Initialise some variables for HSV limits

    Mat frame = imread("Blue_apple.png");

    if ( frame.data == NULL)
    {
        cout << "No image found! Check path." << endl;
        return 1;   //ERROR
    }
    else
    {
        namedWindow("Logo", CV_WINDOW_AUTOSIZE);
        imshow("Logo", frame);
        waitKey();//without this image won't be shown
    }

    // Convert the frame to HSV and apply the limits
    Mat frameHSV, frameHSV_red, frameHSV_blue, frameHSV_green;
    cvtColor(frame, frameHSV, COLOR_BGR2HSV);
     //GET RED COLOUR 1
    inRange(frameHSV, Scalar(lowH_red, lowS_red, lowV_red), Scalar(highH_red, highS, highV), frameHSV_red);

    // GET BLUE COLOUR
    inRange(frameHSV, Scalar(lowH_blue, lowS_blue, lowV_blue), Scalar(highH_blue, highS, highV), frameHSV_blue);

    // GET GREEN COLOUR
    inRange(frameHSV, Scalar(lowH_green, lowS_green, lowV_green), Scalar(highH_green, highS, highV), frameHSV_green);

    redCount = countNonZero(frameHSV_red);
    blueCount = countNonZero(frameHSV_blue);
    greenCount = countNonZero(frameHSV_green);

    if ((redCount > blueCount)&&(redCount > greenCount)){
       cout<<"MAIN OBJECT IS RED"<<endl;
       cout<<redCount<<endl;
       hconcat(frame, frameHSV, frameHSV_red);
       imshow("Red Output", frameHSV_red);

    }
    else if ((blueCount > redCount)&&(blueCount > greenCount)){
            cout<<"MAIN OBJECT IS BLUE"<<endl;
            cout<<blueCount<<endl;
            hconcat(frame, frameHSV, frameHSV_blue);
            imshow("Blue Output", frameHSV_blue);
    }
    else{
        cout<<"MAIN OBJECT IS GREEN"<<endl;
        cout<<greenCount<<endl;
        hconcat(frame, frameHSV, frameHSV_green);
        imshow("Green Output", frameHSV_green);}

    waitKey(0);
    return 0;
