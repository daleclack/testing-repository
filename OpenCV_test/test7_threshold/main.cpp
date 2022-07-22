#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{
    std::string filename;
    Mat image, gray_image, thre_image;
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
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", image);
    namedWindow("Gray Image", WINDOW_AUTOSIZE);
    imshow("Gray Image", gray_image);

    // Use cv::thershold to convert
    threshold(gray_image, thre_image, 0, 255, THRESH_BINARY|THRESH_OTSU);
    namedWindow("OTSU Threshold", WINDOW_AUTOSIZE);
    imwrite("/dev/shm/test.png", thre_image);
    imshow("OTSU Threshold", thre_image);
    
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
