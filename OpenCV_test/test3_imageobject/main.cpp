#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char ** argv){
    // Create image objects
    Mat image = Mat::zeros(Size(400,400), CV_8UC3);
    image = Scalar(255, 0, 0);
    Mat image2 = image.clone();
    image2 = Scalar(0, 225, 0);

    // Create windows
    namedWindow("image1", WINDOW_AUTOSIZE);
    namedWindow("image2", WINDOW_AUTOSIZE);
    imshow("image1", image);
    imshow("image2", image2);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
