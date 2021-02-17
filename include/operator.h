#include <opencv2/opencv.hpp>

// TODO: parallelize
cv::Mat elem_mul(const cv::Mat &mat_a, const cv::Mat &mat_b)
{
    assert(mat_a.rows == mat_b.rows);
    assert(mat_a.cols == mat_b.cols);
    assert(mat_a.channels() == mat_b.channels());
    assert(mat_a.type() == mat_b.type());

    cv::Mat result = cv::Mat::zeros(mat_a.size(), mat_a.type());

    int32_t width = mat_a.cols;
    int32_t height = mat_a.rows;
    int32_t channels = mat_a.channels();
    for (int j = 0; j < height; j++)
    {
        int step = j * width;
        for (int i = 0; i < width; i++)
        {
            int elm = i * mat_a.elemSize();
            for (int c = 0; c < channels; c++)
            {
                result.data[step + elm + c] = mat_a.data[step + elm + c] * mat_b.data[step + elm + c];
            }
        }
    }
    return result;
}
