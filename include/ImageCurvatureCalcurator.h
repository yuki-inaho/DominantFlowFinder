#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "operator.h"

// TODO: use smart pointer?
class ImageCurvatureCalcurator
{
public:
	void calcurate(const cv::Mat &image_8uc1)
	{
		image_8uc1.convertTo(image_32fc1, CV_32FC1, 1.0 / 255);

		_set_first_image_derivatives(image_32fc1);
		_set_second_image_derivatives();
		_calcurate_image_curvature();
	}

	cv::Mat get()
	{
		return _image_curvature;
	};

	cv::Mat operator()(const cv::Mat &image)
	{
		calcurate(image);
		return get();
	}

private:
	cv::Mat _calcurate_image_gradient_x(const cv::Mat &image)
	{
		cv::Mat _image_sobel_x;
		cv::Sobel(image, _image_sobel_x, CV_32FC1, 1, 0, 1);
		return _image_sobel_x;
	}

	cv::Mat _calcurate_image_gradient_y(const cv::Mat &image)
	{
		cv::Mat _image_sobel_y;
		cv::Sobel(image, _image_sobel_y, CV_32FC1, 0, 1, 1);
		return _image_sobel_y;
	}

	void _set_first_image_derivatives(const cv::Mat &image)
	{
		_image_grad_x = _calcurate_image_gradient_x(image);
		_image_grad_y = _calcurate_image_gradient_y(image);
	}

	void _set_second_image_derivatives()
	{
		_image_grad_xx = _calcurate_image_gradient_x(_image_grad_x);
		_image_grad_xy = _calcurate_image_gradient_y(_image_grad_x);
		_image_grad_yx = _calcurate_image_gradient_x(_image_grad_y);
		_image_grad_yy = _calcurate_image_gradient_y(_image_grad_y);
	}

	void _calcurate_image_curvature()
	{	
		/*
		_image_curvature =    elem_mul(_image_grad_y, elem_mul(_image_grad_y, _image_grad_xx)) 
							- elem_mul(_image_grad_x, elem_mul(_image_grad_xy, _image_grad_y))
							- elem_mul(_image_grad_y, elem_mul(_image_grad_yx, _image_grad_x))
							+ elem_mul(_image_grad_x, elem_mul(_image_grad_x, _image_grad_yy));
		*/

		// (15) on Image Denoising Using Mean Curvature of Image Surface
		// https://pdfs.semanticscholar.org/b465/c476e3e7f607c01160538bc2f2a25663286e.pdf

		cv::Mat E = cv::Mat::ones(_image_grad_x.size(), _image_grad_x.type());
		cv::Mat numerator_mat = elem_mul(
									(E + elem_mul(_image_grad_x, _image_grad_x)),
									_image_grad_yy
								)
							-	elem_mul(
									2 * E,				
									elem_mul(
										_image_grad_x,
										elem_mul(_image_grad_y, _image_grad_xy)
									)
								)
							+   elem_mul(
									(E + elem_mul(_image_grad_y, _image_grad_y)),
									_image_grad_xx
								);

		cv::Mat denom_tmp;
		cv::pow(
			E + elem_mul(_image_grad_x, _image_grad_x)  + elem_mul(_image_grad_y, _image_grad_y),
			3.0/2,
			denom_tmp
		);
		cv::Mat denominator_mat = elem_mul(2 * E, denom_tmp) + E * 10e-8;
		_image_curvature = elem_div(numerator_mat, denominator_mat);
	}

	cv::Mat image_32fc1;

	// pseudo first derivatives  on image intensity surface
	cv::Mat _image_grad_x;
	cv::Mat _image_grad_y;

	// pseudo second derivatives  on image intensity surface
	cv::Mat _image_grad_xx;
	cv::Mat _image_grad_xy;
	cv::Mat _image_grad_yx;
	cv::Mat _image_grad_yy;

	// curvatue
	cv::Mat _image_curvature;
};
