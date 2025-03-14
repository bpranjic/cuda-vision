#pragma once

#include "image.h"

using namespace std;

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
    vector<double> getGaussianKernel(unsigned int size, double sigma);

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
    Image horizontalConvolution(const Image& image, const vector<double>& kernel);

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
    Image verticalConvolution(const Image& image, const vector<double>& kernel);

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
    Image gaussianSmooth(const Image& image, unsigned int kernelSize, double sigma);
}  // namespace CUDAVISION
