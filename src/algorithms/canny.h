#include "../image.h"

namespace CUDAVISION
{
    /**
     * @brief Generates a 1d Gaussian Kernel
     * @param size Size of the 1d kernel
     * @param sigma Standard Deviation of the Gaussian kernel
     * @return A std::vector containing the 1d Gaussian kernel
     */
    std::vector<double> getGaussianKernel(int32_t size, double sigma);
    /**
     * @brief Applies a horizontal convolution to an image using a 1D Gaussian kernel.
     *
     * @param image The input image to be convolved.
     * @param kernel The 1D Gaussian kernel used for convolution.
     * @return Image The resulting image after horizontal convolution.
     */
    Image horizontalConvolution(const Image &image, const std::vector<double> &kernel);
    /**
     * @brief Applies a vertical convolution to an image using a 1D Gaussian kernel.
     *
     * @param image The input image to be convolved.
     * @param kernel The 1D Gaussian kernel used for convolution.
     * @return Image The resulting image after vertical convolution.
     */
    Image verticalConvolution(const Image &image, const std::vector<double> &kernel);
    /**
     * @brief Applies Gaussian smoothing to an image.
     *
     * @param image The input image to be smoothed.
     * @param kernelSize The size of the 1D Gaussian kernel.
     * @param sigma The standard deviation of the Gaussian kernel.
     * @return Image The resulting image after Gaussian smoothing.
     */
    Image gaussianSmooth(const Image &image, int32_t kernelSize, double sigma);
} // namespace CUDAVISION
