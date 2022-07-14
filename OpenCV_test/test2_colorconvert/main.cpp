#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;

int main(int argc, char ** argv){
    std::fstream infile;
    char filename[512];

    // Read image filename from file
    infile.open("filename.txt", std::ios_base::in);
    if(infile.is_open()){
        infile.read(filename, sizeof(filename));
    }else{
        std::cout << "No filename.txt" << std::endl;
        return -1;
    }

    std::cout << filename << std::endl;

    // Open the image
    Mat image, image_hsv, image_gray;
    image = imread(filename, IMREAD_COLOR);
    if(image.empty()){
        std::cout << "failed to open the image";
        return -1;
    }
    cvtColor(image, image_hsv, COLOR_BGR2HSV);
    cvtColor(image, image_gray, COLOR_BGR2GRAY);

    // Show the converted images
    namedWindow("Original Image", WINDOW_FREERATIO);
    imshow("Original Image", image);
    namedWindow("HSV Image", WINDOW_FREERATIO);
    imshow("HSV Image", image_hsv);
    namedWindow("Gray Image", WINDOW_FREERATIO);
    imshow("Gray Image", image_gray);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
