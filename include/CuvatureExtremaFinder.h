#pragma once
#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include "typedef.h"
#include "PixelNode.h"
#include "struct.h"
#include "util.h"

class CuvatureExtremaFinder
{
public:
    void set_curvature_image(const cv::Mat &curvature_image)
    {
        _curvature_image = curvature_image.clone();
        _set_image_size(_curvature_image);
    }

    void initialize_pixel_nodes()
    {
        _pixel_node_list = std::vector<PixelNode>(_image_size.width * _image_size.height, PixelNode());
        cv::parallel_for_(cv::Range(0, _image_size.width * _image_size.height), [&](const cv::Range &range) {
            for (size_t r = range.start; r < range.end; r++)
            {
                int32_t y = r / _image_size.width;
                int32_t x = r % _image_size.height;
                Position2D pos_2d = {x, y};
                size_t hash = position2hash(pos_2d, _image_size);
                Position2D pos_neighbor_highest_curvature = _search_relative_high_curvature_position(pos_2d);

                float curvature = _curvature_image.at<float>(y, x);
                PixelNode node = PixelNode(pos_2d, pos_neighbor_highest_curvature, _image_size, curvature);

                _pixel_node_list[hash] = node;
            }
        });
    }

    void set_curvature_order_information()
    {
        // TODO: use bimap
        std::vector<std::size_t> indices_sorted_by_curvature = argsort(_pixel_node_list);


        for(size_t index = 0; index < indices_sorted_by_curvature.size(); index++){
            _map_standard_index_to_curvarture_order_index.insert(
                std::pair<StandardIndex, CurvatureOrderIndex>(index, indices_sorted_by_curvature[index])                
            );
            _map_curvarture_order_index_to_standard_index.insert(
                std::pair<CurvatureOrderIndex, StandardIndex>(indices_sorted_by_curvature[index], index)
            );
        }



        // TODO: write test code with below lines
        /*
        // https://stackoverflow.com/questions/31356570/c-how-to-access-private-member-in-class-inside-stdfor-each
        std::vector<float> sorted_curvature = {};
        std::transform(
            indices_sorted_by_curvature.begin(),
            indices_sorted_by_curvature.end(),
            std::back_inserter(sorted_curvature), 
            [this, &sorted_curvature](const size_t &index) {
                return _pixel_node_list[index].get_curvature();
            }
        );
        */
    }

private:
    void _set_image_size(const cv::Mat &image)
    {
        int32_t image_height = image.rows;
        int32_t image_width = image.cols;
        _image_size = {image_width, image_height};
        std::cout << "<input image size> " << _image_size << std::endl;
    }

    Position2D
    _search_relative_high_curvature_position(Position2D center, int32_t kernel_size = 3)
    {
        float max_curvature = std::numeric_limits<float>::min();
        Position2D pos_neighbor_relative_high_curvature;

        for (size_t k_y = -kernel_size / 2; k_y <= kernel_size / 2; k_y++)
        {
            for (size_t k_x = -kernel_size / 2; k_x <= kernel_size / 2; k_x++)
            {
                Position2D neighbor_pos = {center.x + k_x, center.y + k_y};
                float curvature_neighbor = _curvature_image.at<float>(neighbor_pos.y, neighbor_pos.x);
                if (curvature_neighbor > max_curvature)
                {
                    max_curvature = curvature_neighbor;
                    pos_neighbor_relative_high_curvature = neighbor_pos;
                }
            }
        }
        return pos_neighbor_relative_high_curvature;
    }

    std::vector<PixelNode> _pixel_node_list;

    // TODO: 
    std::unordered_map<StandardIndex, CurvatureOrderIndex> _map_standard_index_to_curvarture_order_index;
    std::unordered_map<CurvatureOrderIndex, StandardIndex> _map_curvarture_order_index_to_standard_index;
    cv::Mat _curvature_image;
    ImageSize _image_size;
};
