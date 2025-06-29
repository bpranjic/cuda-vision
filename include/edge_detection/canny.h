#pragma once

#include "util/image.h"

/**
 * Canny Edge Detection
 * 1. Gaussian Smoothing
 * 2. Finding the intensity gradient of the image
 * 3. Non-maximum suppression
 * 4. Hysteresis Thresholding
 */

namespace CUDAVISION {
    /**
     * @brief Generates a 1d Gaussian Kernel
     *
     * @param size Size of the 1d kernel
     * @param sigma Standard Deviation of the Gaussian kernel
     *
     * @return A std::vector containing the 1d Gaussian kernel
     *
     * @note This method generates a 1-dimensional Gaussian kernel of size 'size' with standard
     * deviation 'sigma'. The highest value is in the center of the vector and the vector is
     * normalized by dividing each element by the sum of all entries.
     *
     */
    std::vector<double> getGaussianKernel(int size, double sigma);

    /**
     * @brief Applies a horizontal convolution to an image using a 1D Gaussian kernel.
     *
     * @param image The input image to be convolved.
     * @param kernel The 1D Gaussian kernel used for convolution.
     *
     * @return Image The resulting image after horizontal convolution.
     *
     * @note This method applies horizontal convolution with a 1-dimensional Gaussian filter. The
     * convolution is applied to each color channel separately and afterwards the channels are
     * recombined.
     *
     */
    Image horizontalConvolution(const Image& image, const std::vector<double>& kernel);

    /**
     * @brief Applies a vertical convolution to an image using a 1D Gaussian kernel.
     *
     * @param image The input image to be convolved.
     * @param kernel The 1D Gaussian kernel used for convolution.
     *
     * @return Image The resulting image after vertical convolution.
     *
     * @note This method applies vertical convolution with a 1-dimensional Gaussian filter. The
     * convolution is applied to each color channel separately and afterwards the channels are
     * recombined.
     *
     */
    Image verticalConvolution(const Image& image, const std::vector<double>& kernel);

    /**
     * @brief Applies Gaussian smoothing to an image.
     *
     * @param image The input image to be smoothed.
     * @param kernelSize The size of the 1D Gaussian kernel.
     * @param sigma The standard deviation of the Gaussian kernel.
     *
     * @return Image, The resulting image after Gaussian smoothing.
     *
     * @note This method applies a Gaussian Blur/Smoothing on an image. Instead of using a
     * 2D-Gaussian Matrix for the convolution, a 1-dimensional convolution on the vertical axis
     * followed by a 1-dimensional convolution on the horizontal axis is performed. This approach is
     * more efficient for larger kernels (O(K) instead of O(K^2)), and can be parallelized more
     * easily.
     *
     */
    Image gaussianSmooth(const Image& image, int kernelSize, double sigma);

    /**
     * @brief Applies the Roberts cross edge detector to an image.
     *
     * @param image The input image to process.
     * @return Image The resulting image showing edge magnitudes.
     *
     * @note This method convolves the image with two 2x2 Roberts Kernels:
     * Gx = [1  0]
     *      [0 -1] and
     * Gy = [0  1]
     *      [-1 0]
     */
    Image robertsOperator(const Image& image);

    /**
     * @brief Applies the Prewitt edge detector to an image.
     *
     * @param image The input image to process.
     * @return Image The resulting image showing edge magnitudes.
     *
     * @note This method convolves the image with two 3x3 Prewitt Kernels:
     * Gx = [ 1   1   1]
     *      [ 0   0   0]
     *      [-1  -1  -1] and
     * Gy = [ 1   0  -1]
     *      [ 1   0  -1]
     *      [ 1   0  -1]
     */
    Image prewittOperator(const Image& image);

    /**
     * @brief Applies the Sobel edge detector to an image.
     *
     * @param image The input image to process.
     * @return Image The resulting image showing edge magnitudes.
     *
     * @note This method convolves the image with two 3x3 Sobel Kernels:
     * Gx = [-1   0   1]
     *      [-2   0   2]
     *      [-1   0   1] and
     * Gy = [-1  -2  -1]
     *      [ 0   0   0]
     *      [ 1   2   1]
     */
    Image sobelOperator(const Image& image);
}  // namespace CUDAVISION
