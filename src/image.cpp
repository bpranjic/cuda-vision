#include "image.h"

#include <fstream>
#include <iostream>

Image::Image(const std::filesystem::path filePath) {
    ifstream file(filePath, ifstream::binary);
    if (!file) {
        cout << "File could not be read" << endl;
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

vector<unsigned char> Image::getPixels() const { return pixels; }

void Image::writeImageToFile(const fs::path filePath) {
    ofstream output(filePath, ofstream::binary);

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
    unsigned int rowSize = ((width * 3 + 3) / 4) * 4;
    for (unsigned int i = 0; i < height; i++) {
        output.write(reinterpret_cast<char*>(&pixels[i * rowSize]), rowSize);
    }
}