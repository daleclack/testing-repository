#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{
    std::string filename;
    Mat image, hsv_image, mask;
    int brightless = 0;

    // Get Filename
    std::cout << "Input Filename:";
    std::cin >> filename;

    // Load the image
    if (filename != "")
    {
        image = imread(filename, IMREAD_COLOR);
        if (image.empty())
        {
            std::cout << "Failed to open the image!" << std::endl;
            return -1;
        }
    }

    // Convert the image to HSV color and filter the background color
    cvtColor(image, hsv_image, COLOR_BGR2HSV);

    // Output the statistics
    double minv, maxv;
    Point minloc, maxloc;
    std::vector<Mat> mv;
    split(image, mv);
    for (int i = 0; i < mv.size(); i++)
    {
        minMaxLoc(mv[i], &minv, &maxv, &minloc, &maxloc);
        std::cout << "min:" << minv << " max:" << maxv << " minloc:"
                  << minloc << " maxloc:" << maxloc << std::endl;
    }
    Mat mean, stddev;
    meanStdDev(image, mean, stddev);
    std::cout << "mean:" << std::endl << mean << std::endl;
    std::cout << "stddev" << std::endl << stddev << std::endl;
    inRange(hsv_image, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
    namedWindow("Image Mask", WINDOW_NORMAL);
    imshow("Image Mask", mask);

    while (1)
    {
        int c = waitKey(1);
        if (c != -1)
        {
            std::cout << c << std::endl;
        }
        if (c == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return 0;
}
