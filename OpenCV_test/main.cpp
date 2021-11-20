#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main(int argc,char ** argv){
    //If no image file name, throw a error
    if(argc != 2){
        std::cout<<"Usage:OpenCV_test <filename>"<<std::endl;
        return -1;
    }

    std::cout<<argv[1]<<std::endl;

    //Create a new image
    Mat image;
    image = imread(argv[1],1);

    //Check if image loaded
    if(!image.data){
        std::cout<<"No Image data"<<std::endl;
        return -1;
    }

    //Create a window to show image
    namedWindow(argv[1],WINDOW_NORMAL);
    imshow(argv[1],image);

    waitKey(0);

    return 0;
}