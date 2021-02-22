#pragma once

#include <opencv2/opencv.hpp>

cv::Mat elem_mul(const cv::Mat &mat_a, const cv::Mat &mat_b)
{
    assert(mat_a.rows == mat_b.rows);
    assert(mat_a.cols == mat_b.cols);
    assert(mat_a.channels() == mat_b.channels());
    assert(mat_a.type() == mat_b.type());

    cv::Mat output = mat_a.mul(mat_b, 1.0); // m*n,  m*n
    return output;
}

cv::Mat elem_div(const cv::Mat &mat_a, const cv::Mat &mat_b)
{
    assert(mat_a.rows == mat_b.rows);
    assert(mat_a.cols == mat_b.cols);
    assert(mat_a.channels() == mat_b.channels());
    assert(mat_a.type() == mat_b.type());

    cv::Mat output;
    cv::divide(mat_a, mat_b, output);
    return output;
}