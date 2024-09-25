#include <iostream>
#include "image.h"
#include "algorithms/canny.h"

int main(){
    Image f1 = Image("images/sample3.bmp");
    std::vector<double> kernel = CUDAVISION::getGaussianKernel(5, 20);
    Image horizontal = CUDAVISION::horizontalConvolution(f1, kernel);
    Image vertical = CUDAVISION::verticalConvolution(f1, kernel);
    horizontal.writeImageToFile("horizontal.bmp");
    vertical.writeImageToFile("vertical.bmp");
    Image blur = CUDAVISION::gaussianSmooth(f1, 5, 20.0);
    blur.writeImageToFile("blur.bmp");
    return 0;
}
