#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{
    std::string filename;
    Mat image;
    int brightless = 0;

    // Get Filename
    std::cout << "Input Filename:";
    std::cin >> filename;

    if (filename != "")
    {
        image = imread(filename, IMREAD_COLOR);
        if (image.empty())
        {
            std::cout << "Failed to open the image!" << std::endl;
            return -1;
        }
    }

    Mat dst = Mat::zeros(image.size(), image.type());
    Mat m = Mat::zeros(image.size(), image.type());
    namedWindow("Image brightless test", WINDOW_NORMAL);
    imshow("Image brightless test", image);

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
        if (c == 45)
        {
            if (brightless > 0)
            {
                brightless -= 5;
            }
            m = Scalar(brightless, brightless, brightless);
            add(image, m, dst);
            imshow("Image brightless test", dst);
        }
        if (c == 61)
        {
            if (brightless < 100)
            {
                brightless += 5;
            }
            m = Scalar(brightless, brightless, brightless);
            add(image, m, dst);
            imshow("Image brightless test", dst);
        }
    }

    destroyAllWindows();
    return 0;
}
