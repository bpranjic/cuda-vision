#include "bitmap.h"
#include "image.h"
#include <fstream>
#include <iostream>

Image readImage(std::string filename){
    std::ifstream file(filename, std::ifstream::binary);
    if (!file){
        std::cout << "File could not be read" << std::endl;
    }

    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    int N = infoHeader.bitmapHeight * infoHeader.bitmapWidth;
    Image image;
    image.height = infoHeader.bitmapHeight;
    image.width = infoHeader.bitmapWidth;
    image.pixels.resize(N*3, 0);
    file.read(image.pixels.data(), image.pixels.size());
    
    return image;
}

Image colorImage(int r, int g, int b, int h, int w){
    Image image;
    image.height = h;
    image.width = w;
    int N = h * w;
    image.pixels.resize(N * 3, 0);
    for (int i = 0; i < N; i++){
        image.pixels[3 * i] = static_cast<char>(b);
        image.pixels[3 * i + 1] = static_cast<char>(g);
        image.pixels[3 * i + 2] = static_cast<char>(r);
    }
    return image;
}

void writeImageToFile(std::string filename, Image image){
    std::ofstream output(filename, std::ofstream::binary);

    BitmapFileHeader fileHeader;
    fileHeader.headerFieldA = 'B';
    fileHeader.headerFieldB = 'M';
    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + image.pixels.size();
    fileHeader.reservedA = 0;
    fileHeader.reservedB = 0;
    fileHeader.imageOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    output.write(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));

    BitmapInfoHeader infoHeader;
    infoHeader.headerSize = sizeof(BitmapInfoHeader);
    infoHeader.bitmapWidth = image.width;
    infoHeader.bitmapHeight = image.height;
    infoHeader.numberOfColorPlanes = 1;
    infoHeader.bitsPerPixel = 24;
    infoHeader.compressionMethod = 0;
    infoHeader.imageSize = 0;
    infoHeader.horizontalResolution = 0;
    infoHeader.verticalResolution = 0;
    infoHeader.colorPalette = 0;
    infoHeader.importantColors = 0; 
    output.write(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    output.write(image.pixels.data(), image.pixels.size());
}

int main(){
    Image green = readImage("images/GRN.bmp");
    writeImageToFile("images/GRN2.bmp", green);

    Image yellow = colorImage(255, 255, 0, 400, 400);
    writeImageToFile("images/YEL.bmp", yellow);

    Image cyan = colorImage(0, 255, 255, 400, 400);
    writeImageToFile("images/CYA.bmp", cyan);

    Image purple = colorImage(255, 0, 255, 400, 400);
    writeImageToFile("images/PRP.bmp", purple);
    return 0;
}
