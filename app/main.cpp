#include <iostream>

#include "canny.h"
#include "image.h"

using namespace std;

int main() {
    Image blue = Image(500, 500, 0, 0, 255);
    blue.writeImageToFile("output/blue.bmp");

    Image sampleImage = Image("images/sample3.bmp");
    vector<double> kernel = CUDAVISION::getGaussianKernel(5, 20.0);
    Image horizontal = CUDAVISION::horizontalConvolution(sampleImage, kernel);
    Image vertical = CUDAVISION::verticalConvolution(sampleImage, kernel);
    horizontal.writeImageToFile("output/horizontal.bmp");
    vertical.writeImageToFile("output/vertical.bmp");

    Image blur = CUDAVISION::gaussianSmooth(sampleImage, 5, 20.0);
    blur.writeImageToFile("output/blur.bmp");

    return 0;
}
