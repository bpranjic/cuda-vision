#include "image.h"
#include <iostream>
#include <fstream>

Image::Image(uint32_t width, uint32_t height) : width(width), height(height){}

Image::Image(const Image &other){
    width = other.width;
    height = other.height;
    pixels = other.pixels;
}

Image::Image(const std::filesystem::path filePath){
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file){
        std::cout << "File could not be read" << std::endl;
    } 
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    int N = infoHeader.bitmapHeight * infoHeader.bitmapWidth;
    height = infoHeader.bitmapHeight;
    width = infoHeader.bitmapWidth;
    pixels.resize(N*3, 0);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
}

Image::Image(uint32_t width, uint32_t height, uint8_t r, uint8_t g, uint8_t b) : width(width), height(height){
    int N = height * width;
    pixels.resize(N * 3, 0);
    for (int i = 0; i < N; i++){
        pixels[3 * i] = b;
        pixels[3 * i + 1] = g;
        pixels[3 * i + 2] = r;
    }
}

Image::~Image(){}

u_int32_t Image::getHeight() { return height; }

u_int32_t Image::getWidth() { return width; }

void Image::writeImageToFile(const std::filesystem::path filePath){
    std::ofstream output(filePath, std::ofstream::binary);

    BitmapFileHeader fileHeader;
    fileHeader.headerFieldA = 'B';
    fileHeader.headerFieldB = 'M';
    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + pixels.size();
    fileHeader.reservedA = 0;
    fileHeader.reservedB = 0;
    fileHeader.imageOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    output.write(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));

    BitmapInfoHeader infoHeader;
    infoHeader.headerSize = sizeof(BitmapInfoHeader);
    infoHeader.bitmapWidth = width;
    infoHeader.bitmapHeight = height;
    infoHeader.numberOfColorPlanes = 1;
    infoHeader.bitsPerPixel = 24;
    infoHeader.compressionMethod = 0;
    infoHeader.imageSize = 0;
    infoHeader.horizontalResolution = 0;
    infoHeader.verticalResolution = 0;
    infoHeader.colorPalette = 0;
    infoHeader.importantColors = 0; 
    output.write(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    output.write(reinterpret_cast<char*>(pixels.data()), pixels.size());
}