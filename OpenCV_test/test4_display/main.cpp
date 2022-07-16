#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{
    // Create capture object to capture video
    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        std::cout << "Can't open video device!" << std::endl;
        return -1;
    }

    // properties
    double rate = capture.get(CAP_PROP_FPS);
    double width = capture.get(CAP_PROP_FRAME_WIDTH);
    double height = capture.get(CAP_PROP_FRAME_HEIGHT);

    // Information about the camera
    std::cout << "Frame Rate = " << rate << "width = " << width << "height = " << height << std::endl;

    namedWindow("Video Capture", WINDOW_NORMAL);

    Mat frame;
    while (1)
    {
        if (!capture.read(frame))
        {
            std::cout << "no video frame" << std::endl;
            continue;
        }

        imshow("Video Capture", frame);
        int c = waitKey(1);
        if(c == 27){
            break;
        }
    }

    capture.release();
    return 0;
}
