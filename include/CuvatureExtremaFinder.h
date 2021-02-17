#pragma once
#include <opencv2/opencv.hpp>
#include "PixelNode.h"
#include "struct.h"

class CuvatureExtremaFinder
{
public:
    void set_curvature_image(const cv::Mat &curvature_image)
    {
        _curvature_image = curvature_image;
        _set_image_size(_curvature_image);
    }

    void initialize_pixel_nodes()
    {
        cv::parallel_for_(cv::Range(0,  _image_size.width * _image_size.height), [&](const cv::Range &range) {
            for (int32_t r = range.start; r < range.end; r++)
            {
                int32_t y = r / _image_size.width;
                int32_t x = r % _image_size.height;
                Position2D pos_2d = {x, y};
                float curvature = _curvature_image.at<float>(y, x);

            }
        });
        //pass
    }

private:
    void _set_image_size(const cv::Mat &image)
    {
        int32_t image_height = image.rows;
        int32_t image_width = image.cols;
        _image_size = {image_width, image_height};
    }

    std::vector<PixelNode> _pixel_node_list;
    cv::Mat _curvature_image;
    ImageSize _image_size;
};
