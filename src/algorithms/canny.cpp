#include "canny.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace CUDAVISION {
    vector<double> getGaussianKernel(unsigned int size, double sigma) {
        vector<double> kernel(size);
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

    Image horizontalConvolution(const Image& image, const vector<double>& kernel) {
        int height = image.getHeight();
        int width = image.getWidth();
        const vector<unsigned char>& pixels = image.getPixels();
        vector<unsigned char> outputPixels(3 * height * width);
        int kernelMid = kernel.size() / 2;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double sumR = 0.0, sumG = 0.0, sumB = 0.0;
                for (int k = -kernelMid; k <= kernelMid; k++) {
                    int px = min(max(j + k, 0), width - 1);
                    sumB += pixels[3 * (i * width + px)] * kernel[k + kernelMid];
                    sumG += pixels[3 * (i * width + px) + 1] * kernel[k + kernelMid];
                    sumR += pixels[3 * (i * width + px) + 2] * kernel[k + kernelMid];
                }

                int pixelIdx = i * width + j;
                outputPixels[3 * pixelIdx] = static_cast<unsigned char>(min(max(sumB, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 1] =
                    static_cast<unsigned char>(min(max(sumG, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 2] =
                    static_cast<unsigned char>(min(max(sumR, 0.0), 255.0));
            }
        }

        return Image(width, height, outputPixels);
    }

    Image verticalConvolution(const Image& image, const vector<double>& kernel) {
        int height = image.getHeight();
        int width = image.getWidth();
        const vector<unsigned char>& pixels = image.getPixels();
        vector<unsigned char> outputPixels(3 * height * width);
        int kernelMid = kernel.size() / 2;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double sumR = 0.0, sumG = 0.0, sumB = 0.0;
                for (int k = -kernelMid; k <= kernelMid; k++) {
                    int py = min(max(i + k, 0), height - 1);
                    sumB += pixels[3 * (py * width + j)] * kernel[k + kernelMid];
                    sumG += pixels[3 * (py * width + j) + 1] * kernel[k + kernelMid];
                    sumR += pixels[3 * (py * width + j) + 2] * kernel[k + kernelMid];
                }

                int pixelIdx = i * width + j;
                outputPixels[3 * pixelIdx] = static_cast<unsigned char>(min(max(sumB, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 1] =
                    static_cast<unsigned char>(min(max(sumG, 0.0), 255.0));
                outputPixels[3 * pixelIdx + 2] =
                    static_cast<unsigned char>(min(max(sumR, 0.0), 255.0));
            }
        }

        return Image(width, height, outputPixels);
    }

    Image gaussianSmooth(const Image& image, unsigned int kernelSize, double sigma) {
        vector<double> kernel = getGaussianKernel(kernelSize, sigma);
        Image tempImage = image;
        for (int i = 0; i < 3; i++) {
            tempImage = verticalConvolution(tempImage, kernel);
        }
        for (int i = 0; i < 3; i++) {
            tempImage = horizontalConvolution(tempImage, kernel);
        }
        return tempImage;
    }
}  // namespace CUDAVISION