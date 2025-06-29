#include "util/image.h"

#include <fstream>
#include <iostream>

Image::Image(const std::filesystem::path filePath) {
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file) {
        std::cerr << "File could not be read" << std::endl;
        return;
    }
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    unsigned long long N = infoHeader.bitmapHeight * infoHeader.bitmapWidth;
    height = infoHeader.bitmapHeight;
    width = infoHeader.bitmapWidth;
    unsigned int rowSize = ((width * 3 + 3) / 4) * 4;
    pixels.resize(height * rowSize, 0);
    file.seekg(fileHeader.imageOffset);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
}

Image::Image(unsigned int width, unsigned int height, unsigned char r, unsigned char g,
             unsigned char b)
    : width(width), height(height) {
    unsigned int N = height * width;
    pixels.resize(N * 3, 0);
    for (unsigned int i = 0; i < N; i++) {
        pixels[3 * i] = b;
        pixels[3 * i + 1] = g;
        pixels[3 * i + 2] = r;
    }
}

unsigned int Image::getHeight() const { return height; }

unsigned int Image::getWidth() const { return width; }

std::vector<unsigned char> Image::getPixels() const { return pixels; }

void Image::writeImageToFile(const fs::path filePath) {
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
    infoHeader.bitsPerPixel = 8 * (pixels.size() / (width * height));
    infoHeader.compressionMethod = 0;
    infoHeader.imageSize = 0;
    infoHeader.horizontalResolution = 0;
    infoHeader.verticalResolution = 0;
    infoHeader.colorPalette = 0;
    infoHeader.importantColors = 0;
    output.write(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    unsigned int rowSize = ((width * 3 + 3) / 4) * 4;
    for (unsigned int i = 0; i < height; i++) {
        output.write(reinterpret_cast<char*>(&pixels[i * rowSize]), rowSize);
    }
}

Image Image::toGrayscale() {
    const size_t size = width * height;
    std::vector<uint8_t> grayscalePixels(size * 3);

    for (size_t i = 0; i < size; i++) {
        unsigned char b = pixels[3 * i + 0];
        unsigned char g = pixels[3 * i + 1];
        unsigned char r = pixels[3 * i + 2];
        unsigned char gray = static_cast<unsigned char>(0.114f * b + 0.587f * g + 0.299f * r);
        grayscalePixels[3 * i + 0] = gray;
        grayscalePixels[3 * i + 1] = gray;
        grayscalePixels[3 * i + 2] = gray;
    }

    return Image(width, height, grayscalePixels);
}