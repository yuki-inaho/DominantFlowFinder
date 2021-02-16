#include <iostream>
#include <opencv2/opencv.hpp>
#include "Graph.h"
#include "Node.h"


int main(int argc, char **argv)
{
    cv::Mat rgb_image = cv::imread("../data/image.png");
    cv::Mat gray_image;
    cv::cvtColor(rgb_image, gray_image, cv::COLOR_RGB2GRAY);

    cv::imwrite("../gray.png", gray_image);    
    return 0;
}