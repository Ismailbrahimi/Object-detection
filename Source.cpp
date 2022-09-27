
//BRAHIMI Ismail
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "Windows.h"
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

const String video_original = "video_original";
const String video_capture = "video_capture";
cv::Scalar bluelow = cv::Scalar(110, 50, 50);
cv::Scalar bluehigh = cv::Scalar(130, 255, 255);

void CoordFunc(int event, int x, int y, int flags, void* userdata)
{   
    if (event == EVENT_MOUSEMOVE)
    {
        cout << "Mouvement du curseur - coordonnees (" << x << ", " << y << ")" << endl;

    }
}

int main(int argc, char** argv)
{
    VideoCapture cap(0);
    namedWindow(video_original);
    namedWindow(video_capture);

    Mat video, frame_HSV, video_detection;
    while (true) {
        cap >> video;
        if (video.empty())
        {
            break;
        }
        // BGR to HSV 
        cv::cvtColor(video, frame_HSV, COLOR_BGR2HSV);
        // Detection based on the HSV 
        inRange(frame_HSV, bluelow, bluehigh, video_detection);

        //set the callback function for any mouse event
        setMouseCallback("video_capture", CoordFunc, NULL);


        // find moments of the image
        Moments m = moments(video_detection);
        Point p(m.m10 / m.m00, m.m01 / m.m00);

        // coordinates of centroid
        cout << Mat(p) << endl;

        // show the image with a point mark at the centroid
        circle(video_detection, p, 5, Scalar(128, 0, 0), -1);

        SetCursorPos(p.x, p.y);

        imshow(video_original, video);
        imshow(video_capture, video_detection);
        char key = (int)waitKey(1);
        if (key == 27)
        {
            break;
        }
    }
    return 0;

}