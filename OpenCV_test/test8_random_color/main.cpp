#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{
    Mat canvas = Mat::zeros(512, 512, CV_8UC3);
    RNG rng1(12345);
    int w = canvas.cols;
    int h = canvas.rows;
    namedWindow("Color test", WINDOW_AUTOSIZE);
    
    while (1)
    {
        int c = waitKey(30);
        if (c != -1)
        {
            std::cout << c << std::endl;
        }
        if (c == 27)
        {
            break;
        }
        // Clear the canvas
        canvas = Scalar(0,0,0);
        
        // Get position and color
        int x1 = rng1.uniform(0,w);
        int y1 = rng1.uniform(0,h);
        int x2 = rng1.uniform(0,w);
        int y2 = rng1.uniform(0,h);
        int r = rng1.uniform(0,255);
        int g = rng1.uniform(0,255);
        int b = rng1.uniform(0,255);

        // Draw lines
        line(canvas, Point(x1, y1), Point(x2, y2), Scalar(r,g,b), 2, LINE_AA, 0);
        imshow("Color test", canvas);
    }

    destroyAllWindows();
    return 0;
}
