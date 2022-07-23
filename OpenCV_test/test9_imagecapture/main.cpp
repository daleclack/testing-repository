#include <opencv2/opencv.hpp>
#include "../../json_nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace cv;
using json = nlohmann::json;

int main(int argc, char **argv)
{
    // Read Config from json file
    std::string path;
    std::ifstream config_file("config_collect.json");
    if (config_file.is_open())
    {
        json data = json::parse(config_file);
        path = data["path"];
        if (path[path.length() - 1] != '/')
        {
            path = path + "/";
        }
    }
    else
    {
        path = "./";
    }

    // Start Video Capture
    bool CollectEnabled = false;
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
        // read frame from video capture
        if (!capture.read(frame))
        {
            std::cout << "no video frame" << std::endl;
            continue;
        }

        // Show the image of frame
        imshow("Video Capture", frame);

        // Write frame to file
        static int count = 0;
        if (CollectEnabled)
        {
            count++;
            std::string filename = path + std::to_string(count) + ".jpg";
            imwrite(filename, frame);
        }

        int c = waitKey(10);

        if (c == 27)
        {
            break;
        }
        if (c == 99)
        {
            CollectEnabled = !CollectEnabled;
        }
    }

    capture.release();
    destroyAllWindows();
    return 0;
}
