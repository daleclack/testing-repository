#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char ** argv){
    std::string filename, save_images;

    std::cin >> filename;
    std::cout << "Save gray and hsv images? (Y/N)";
    std::cin >> save_images;

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

    // Write the images
    imwrite("image_gray.png", image_gray);
    imwrite("image_hsv.png", image_hsv);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
