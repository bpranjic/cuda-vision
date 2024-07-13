#include <vector>
#include <cmath>
#include <cstdint>
#include "canny.h"

namespace CUDAVISION
{
    /**
     * Canny Edge Detection
     * 1. Gaussian Smoothing
     * 2. Finding the intensity gradient of the image
     * 3. Non-maximum suppression
     * 4. Hysteresis Thresholding
     */

    /**
     * This method generates a 1-dimensional Gaussian kernel of size @param size with
     * standard deviation @param sigma. The highest value is in the center of the vector
     * and the vector is normalized by dividing each element by the sum of all entries.
     */
    std::vector<double> getGaussianKernel(int32_t size, double sigma)
    {
        std::vector<double> kernel(size);
        double sum = 0.0;
        int32_t mid = size / 2;

        for (int i = -mid; i <= mid; i++)
        {
            kernel[i + mid] = exp(-(i * i) / (2 * sigma * sigma) / (M_PI * 2 * sigma * sigma));
            sum += kernel[i + mid];
        }

        for (int i = 0; i < size; i++)
        {
            kernel[i] /= sum;
        }

        return kernel;
    }

    /**
     * This method applies horizontal convolution with a 1-dimensional Gaussian filter.
     * The convolution is applied to each color channel separately and afterwards the channels are 
     * recombined.
     */
    Image horizontalConvolution(const Image &image, const std::vector<double> &kernel)
    {
        int32_t height = image.getHeight();
        int32_t width = image.getWidth();
        const std::vector<uint8_t> &pixels = image.getPixels();
        std::vector<uint8_t> outputPixels(3 * height * width);
        int32_t kernelMid = kernel.size() / 2;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                double sumR = 0.0, sumG = 0.0, sumB = 0.0;
                for (int k = -kernelMid; k <= kernelMid; k++)
                {
                    int px = std::min(std::max(j + k, 0), width - 1);
                    sumB += pixels[3 * (i * width + px)] * kernel[k + kernelMid];
                    sumG += pixels[3 * (i * width + px) + 1] * kernel[k + kernelMid];
                    sumR += pixels[3 * (i * width + px) + 2] * kernel[k + kernelMid];
                }

                int pixelIdx = i * width + j;
                outputPixels[3 * pixelIdx] = static_cast<uint8_t>(std::min(std::max(sumB, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 1] = static_cast<uint8_t>(std::min(std::max(sumG, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 2] = static_cast<uint8_t>(std::min(std::max(sumR, 0.0), 255.0));
            }
        }

        return Image(width, height, outputPixels);
    }

    /**
     * This method applies vertical convolution with a 1-dimensional Gaussian filter.
     * The convolution is applied to each color channel separately and afterwards the channels are 
     * recombined.
     */
    Image verticalConvolution(const Image &image, const std::vector<double> &kernel)
    {
        int32_t height = image.getHeight();
        int32_t width = image.getWidth();
        const std::vector<uint8_t> &pixels = image.getPixels();
        std::vector<uint8_t> outputPixels(3 * height * width);
        int32_t kernelMid = kernel.size() / 2;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                double sumR = 0.0, sumG = 0.0, sumB = 0.0;
                for (int k = -kernelMid; k <= kernelMid; k++)
                {
                    int py = std::min(std::max(i + k, 0), height - 1);
                    sumB += pixels[3 * (py * width + j)] * kernel[k + kernelMid];
                    sumG += pixels[3 * (py * width + j) + 1] * kernel[k + kernelMid];
                    sumR += pixels[3 * (py * width + j) + 2] * kernel[k + kernelMid];
                }

                int pixelIdx = i * width + j;
                outputPixels[3 * pixelIdx] = static_cast<uint8_t>(std::min(std::max(sumB, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 1] = static_cast<uint8_t>(std::min(std::max(sumG, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 2] = static_cast<uint8_t>(std::min(std::max(sumR, 0.0), 255.0));
            }
        }

        return Image(width, height, outputPixels);
    }

    /**
     * This method applies a Gaussian Blur/Smoothing on an image. Instead of using a 2D-Gaussian Matrix
     * for the convolution, I perform a 1-dimensional convolution on the vertical axis followed by 
     * a 1-dimensional convolution on the horizontal axis. This approach is more efficient for larger
     * kernels (O(K) instead of O(K^2)), and can be parallelized more easily.
     */
    Image gaussianSmooth(const Image &image, int32_t kernelSize, double sigma)
    {
        std::vector<double> kernel = getGaussianKernel(kernelSize, sigma);
        Image tempImage = image;
        for (int i = 0; i < 3; i++)
        {
            tempImage = verticalConvolution(tempImage, kernel);
        }
        for (int i = 0; i < 3; i++)
        {
            tempImage = horizontalConvolution(tempImage, kernel);
        }
        return tempImage;
    }
}