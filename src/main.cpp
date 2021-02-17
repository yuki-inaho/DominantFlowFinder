#include <iostream>
#include <opencv2/opencv.hpp>

#include "util.h"
#include "Graph.h"
#include "ImageCurvatureCalcurator.h"
#include "PixelNode.h"

std::string PARENT_DIR = getParentDir();

int main(int argc, char **argv)
{
    cv::Mat rgb_image = cv::imread("../data/image.png");
    cv::Mat gray_image;
    cv::cvtColor(rgb_image, gray_image, cv::COLOR_RGB2GRAY);

    ImageCurvatureCalcurator curvature_calcurtor;
    curvature_calcurtor.calcurate(gray_image);
    cv::Mat image_curvature = curvature_calcurtor.get();

    // dump image
    std::string dir_name = concatDirectoryAndDataNames(PARENT_DIR, "output");
    std::string data_save_name = "curvature.yml";
    mkdir(dir_name);
    std::string save_path_str = concatDirectoryAndDataNames(dir_name, data_save_name);
    dumpCVMat(save_path_str, image_curvature);

    cv::imwrite("../gray.png", gray_image);
    return 0;
}