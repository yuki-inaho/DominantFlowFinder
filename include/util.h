#pragma once

#include <opencv2/opencv.hpp>
#include <experimental/filesystem>
#include <numeric>
#include "struct.h"

namespace fs = std::experimental::filesystem ;

std::string concatDirectoryAndDataNames(std::string dir_name, std::string data_name){
    fs::path save_path = "";
    save_path.append(dir_name);
    save_path.append(data_name);
    return save_path.string<char>();
}

std::string getParentDir(){
    // assume executive file is exist on {ParentDIR}/build
    fs::path parent_dir_path = fs::canonical("..");    
    return parent_dir_path.string<char>(); 
}

cv::Mat drawExtremaPoints(cv::Mat &image, std::vector<Position2D> extrema_pos_list){
    cv::Mat image_extrema = image.clone();
    int32_t n_extrema = extrema_pos_list.size();
    for(size_t i = 0; i < n_extrema; i++){
        cv::Point cv_point(extrema_pos_list[i].x, extrema_pos_list[i].y);
        cv::circle(image_extrema, cv_point, 1, cv::Scalar(255,0,0), 1);
    }
    return image_extrema;
}

bool mkdir(std::string dir_name){
    return fs::create_directory(dir_name);
}

void dumpCVMat(std::string name, const cv::Mat &image)
{
    cv::FileStorage fs(name, cv::FileStorage::WRITE);
    fs << "mat" << image;
};

template <typename T>
std::vector<size_t> argsort(std::vector<T> sequence, bool ascending=false){
    std::vector<size_t> indices(sequence.size());    
    std::iota(indices.begin(), indices.end(), 0);
    if(ascending){
        std::sort(indices.begin(), indices.end(), [&sequence](size_t i1, size_t i2) {
            return sequence[i1] < sequence[i2];
        });
    }else{
        std::sort(indices.begin(), indices.end(), [&sequence](size_t i1, size_t i2) {
            return sequence[i1] > sequence[i2];
        });
    }
    return indices;
}