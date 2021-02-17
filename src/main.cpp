#include <iostream>
#include <opencv2/opencv.hpp>

#include "argparse.hpp"
#include "util.h"
#include "Graph.h"
#include "ImageCurvatureCalcurator.h"
#include "CuvatureExtremaFinder.h"
#include "PixelNode.h"

std::string PARENT_DIR = getParentDir();

struct ParsedArgument{
    bool save_image_curvature;
};

ParsedArgument parse_args(int argc, char **argv){
    argparse::ArgumentParser parser("dominant_flow_finder", "Calcurate dominant flow", "MIT");
    parser.addArgument({"--save-image-curvature", "-s"}, "flag", argparse::ArgumentType::StoreTrue);
    auto args = parser.parseArgs(argc, argv);
    bool save_image_curvature = args.has("save-image-curvature");
    ParsedArgument parsed_args = {save_image_curvature};
    return parsed_args;
}

int main(int argc, char **argv)
{
    ParsedArgument args = parse_args(argc, argv);
    
    cv::Mat rgb_image = cv::imread("../data/image.png");
    cv::Mat gray_image;
    cv::cvtColor(rgb_image, gray_image, cv::COLOR_RGB2GRAY);

    ImageCurvatureCalcurator curvature_calcurtor;
    curvature_calcurtor.calcurate(gray_image);
    cv::Mat image_curvature = curvature_calcurtor.get();

    CuvatureExtremaFinder curvature_extrema_finder;
    curvature_extrema_finder.set_curvature_image(image_curvature);
    curvature_extrema_finder.initialize_pixel_nodes();

    // dump image
    if (args.save_image_curvature)
    {
        std::string dir_name = concatDirectoryAndDataNames(PARENT_DIR, "output");
        std::string data_save_name = "curvature.xml";
        mkdir(dir_name);
        std::string save_path_str = concatDirectoryAndDataNames(dir_name, data_save_name);
        dumpCVMat(save_path_str, image_curvature);
    }

    cv::imwrite("../gray.png", gray_image);
    return 0;
}