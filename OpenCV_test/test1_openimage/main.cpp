#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace cv;

int main(int argc,char ** argv){
    std::fstream infile;
    char filename[128];

    infile.open("filename.txt",std::ios_base::in);
    if(infile.is_open()){
        infile.read(filename, sizeof(filename));
    }

    // //If no image file name, throw a error
    // if(argc != 2){
    //     std::cout<<"Usage:OpenCV_test <filename>"<<std::endl;
    //     return -1;
    // }

    // std::cout<<argv[1]<<std::endl;

    //Create a new image
    Mat image, image2;
    image = imread(filename, IMREAD_COLOR);
    image2 = imread(filename, IMREAD_GRAYSCALE);

    //Check if image loaded
    if(!image.data){
        std::cout<<"No Image data"<<std::endl;
        return -1;
    }

    //Create a window to show image
    namedWindow(filename,WINDOW_NORMAL);
    imshow(filename,image);

    namedWindow("Gray image", WINDOW_NORMAL);
    imshow("Gray image",image2);

    waitKey(0);
    destroyAllWindows();

    return 0;
}