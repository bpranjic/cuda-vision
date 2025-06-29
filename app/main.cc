#include <iostream>

#include "edge_detection/canny.h"
#include "util/image.h"

int main() {
    Image sampleImage = Image("images/sample3.bmp");
    std::vector<double> kernel = CUDAVISION::getGaussianKernel(5, 20.0);
    Image blur = CUDAVISION::gaussianSmooth(sampleImage, 5, 20.0);
    blur.writeImageToFile("output/blur.bmp");
    Image grayscale = blur.toGrayscale();
    Image roberts = CUDAVISION::robertsOperator(grayscale);
    roberts.writeImageToFile("output/roberts.bmp");
    Image prewitt = CUDAVISION::prewittOperator(grayscale);
    prewitt.writeImageToFile("output/prewitt.bmp");
    Image sobel = CUDAVISION::sobelOperator(grayscale);
    sobel.writeImageToFile("output/sobel.bmp");
    return 0;
}
