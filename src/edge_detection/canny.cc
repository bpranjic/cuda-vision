#include "edge_detection/canny.h"

#include <cmath>
#include <vector>

namespace CUDAVISION {
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
    std::vector<double> getGaussianKernel(int size, double sigma) {
        std::vector<double> kernel(size);
        double sum = 0.0;
        int mid = size / 2;

        for (int i = -mid; i <= mid; i++) {
            kernel[i + mid] = exp(-(i * i) / (2 * sigma * sigma) / (M_PI * 2 * sigma * sigma));
            sum += kernel[i + mid];
        }

        for (int i = 0; i < size; i++) {
            kernel[i] /= sum;
        }

        return kernel;
    }

    Image horizontalConvolution(const Image& image, const std::vector<double>& kernel) {
        int height = image.getHeight();
        int width = image.getWidth();
        const std::vector<unsigned char>& pixels = image.getPixels();
        std::vector<unsigned char> outputPixels(3 * height * width);
        int kernelMid = kernel.size() / 2;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double sumR = 0.0, sumG = 0.0, sumB = 0.0;
                for (int k = -kernelMid; k <= kernelMid; k++) {
                    int px = std::min(std::max(j + k, 0), width - 1);
                    sumB += pixels[3 * (i * width + px)] * kernel[k + kernelMid];
                    sumG += pixels[3 * (i * width + px) + 1] * kernel[k + kernelMid];
                    sumR += pixels[3 * (i * width + px) + 2] * kernel[k + kernelMid];
                }

                int pixelIdx = i * width + j;
                outputPixels[3 * pixelIdx] =
                    static_cast<unsigned char>(std::min(std::max(sumB, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 1] =
                    static_cast<unsigned char>(std::min(std::max(sumG, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 2] =
                    static_cast<unsigned char>(std::min(std::max(sumR, 0.0), 255.0));
            }
        }

        return Image(width, height, outputPixels);
    }

    Image verticalConvolution(const Image& image, const std::vector<double>& kernel) {
        int height = image.getHeight();
        int width = image.getWidth();
        const std::vector<unsigned char>& pixels = image.getPixels();
        std::vector<unsigned char> outputPixels(3 * height * width);
        int kernelMid = kernel.size() / 2;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double sumR = 0.0, sumG = 0.0, sumB = 0.0;
                for (int k = -kernelMid; k <= kernelMid; k++) {
                    int py = std::min(std::max(i + k, 0), height - 1);
                    sumB += pixels[3 * (py * width + j)] * kernel[k + kernelMid];
                    sumG += pixels[3 * (py * width + j) + 1] * kernel[k + kernelMid];
                    sumR += pixels[3 * (py * width + j) + 2] * kernel[k + kernelMid];
                }

                int pixelIdx = i * width + j;
                outputPixels[3 * pixelIdx] =
                    static_cast<unsigned char>(std::min(std::max(sumB, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 1] =
                    static_cast<unsigned char>(std::min(std::max(sumG, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 2] =
                    static_cast<unsigned char>(std::min(std::max(sumR, 0.0), 255.0));
            }
        }

        return Image(width, height, outputPixels);
    }

    Image gaussianSmooth(const Image& image, int kernelSize, double sigma) {
        std::vector<double> kernel = getGaussianKernel(kernelSize, sigma);
        Image tempImage = image;
        for (int i = 0; i < 3; i++) {
            tempImage = verticalConvolution(tempImage, kernel);
        }
        for (int i = 0; i < 3; i++) {
            tempImage = horizontalConvolution(tempImage, kernel);
        }
        return tempImage;
    }

    Image robertsOperator(const Image& image) {
        std::vector<int> kx = {1, 0, 0, -1};
        std::vector<int> ky = {0, 1, -1, 0};
        unsigned int height = image.getHeight();
        unsigned int width = image.getWidth();
        const auto& pixels = image.getPixels();
        std::vector<unsigned char> outputPixels(3 * height * width, 0);

        for (int i = 0; i < height - 1; i++) {
            for (int j = 0; j < width - 1; j++) {
                int idx = 3 * (i * width + j);
                for (int c = 0; c < 3; c++) {
                    int gx = kx[0] * pixels[idx + c] + kx[3] * pixels[idx + 3 * (width + 1) + c];
                    int gy = ky[1] * pixels[idx + 3 + c] + ky[2] * pixels[idx + 3 * width + c];
                    int gradient = static_cast<int>(std::sqrt(gx * gx + gy * gy));
                    outputPixels[idx + c] =
                        static_cast<unsigned char>(std::min(255, std::max(0, gradient)));
                }
            }
        }
        return Image(width, height, outputPixels);
    }

    Image prewittOperator(const Image& image) {
        std::vector<int> kx = {1, 1, 1, 0, 0, 0, -1, -1, -1};
        std::vector<int> ky = {1, 0, -1, 1, 0, -1, 1, 0, -1};
        unsigned int height = image.getHeight();
        unsigned int width = image.getWidth();
        const auto& pixels = image.getPixels();
        std::vector<unsigned char> outputPixels(3 * height * width, 0);

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                int idx = 3 * (i * width + j);
                for (int c = 0; c < 3; c++) {
                    int gx = 0, gy = 0;
                    for (int ki = 0; ki < 3; ki++) {
                        for (int kj = 0; kj < 3; kj++) {
                            int weightX = kx[ki * 3 + kj];
                            int weightY = ky[ki * 3 + kj];
                            int nidx = 3 * ((i + ki - 1) * width + (j + kj - 1)) + c;
                            gx += weightX * pixels[nidx];
                            gy += weightY * pixels[nidx];
                        }
                    }
                    int gradient = static_cast<int>(std::sqrt(gx * gx + gy * gy));
                    outputPixels[idx + c] =
                        static_cast<unsigned char>(std::min(255, std::max(0, gradient)));
                }
            }
        }
        return Image(width, height, outputPixels);
    }

    Image sobelOperator(const Image& image) {
        std::vector<int> kx = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
        std::vector<int> ky = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
        unsigned int height = image.getHeight();
        unsigned int width = image.getWidth();
        const auto& pixels = image.getPixels();
        std::vector<unsigned char> outputPixels(3 * height * width, 0);

        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                int idx = 3 * (i * width + j);
                for (int c = 0; c < 3; c++) {
                    int gx = 0, gy = 0;
                    for (int ki = 0; ki < 3; ki++) {
                        for (int kj = 0; kj < 3; kj++) {
                            int weightX = kx[ki * 3 + kj];
                            int weightY = ky[ki * 3 + kj];
                            int nidx = 3 * ((i + ki - 1) * width + (j + kj - 1)) + c;
                            gx += weightX * pixels[nidx];
                            gy += weightY * pixels[nidx];
                        }
                    }
                    int gradient = static_cast<int>(std::sqrt(gx * gx + gy * gy));
                    outputPixels[idx + c] =
                        static_cast<unsigned char>(std::min(255, std::max(0, gradient)));
                }
            }
        }
        return Image(width, height, outputPixels);
    }
}  // namespace CUDAVISION