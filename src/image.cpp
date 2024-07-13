#include <iostream>
#include <fstream>
#include "image.h"

/**
 * Constructor that accepts width and height. Creates an empty image.
 */
Image::Image(uint32_t width, uint32_t height) : width(width), height(height) {}

/**
 * Constructor that accepts width, height and pixels
 */
Image::Image(uint32_t width, uint32_t height, std::vector<uint8_t> pixels) : width(width), height(height), pixels(pixels) {}

/**
 * Copy-constructor
 */
Image::Image(const Image &other) : width(other.width), height(other.height), pixels(other.pixels) {}

/**
 * Creates an image from a file. At the moment only Bitmap files are supported, especially
 * Bitmap versions V3 and V5.
 */
Image::Image(const std::filesystem::path filePath)
{
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file)
    {
        std::cout << "File could not be read" << std::endl;
    }
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    file.read(reinterpret_cast<char *>(&fileHeader), sizeof(BitmapFileHeader));
    file.read(reinterpret_cast<char *>(&infoHeader), sizeof(BitmapInfoHeader));
    uint32_t N = infoHeader.bitmapHeight * infoHeader.bitmapWidth;
    height = infoHeader.bitmapHeight;
    width = infoHeader.bitmapWidth;
    uint32_t rowSize = ((width * 3 + 3) / 4) * 4;
    pixels.resize(height * rowSize, 0);
    file.seekg(fileHeader.imageOffset); // start reading from correct position, can vary depending on V5 or V3 header
    file.read(reinterpret_cast<char *>(pixels.data()), pixels.size());
}

/**
 * This constructor is used to create an image of a solid color.
 */
Image::Image(uint32_t width, uint32_t height, uint8_t r, uint8_t g, uint8_t b) : width(width), height(height)
{
    uint32_t N = height * width;
    pixels.resize(N * 3, 0);
    for (int i = 0; i < N; i++)
    {
        pixels[3 * i] = b;
        pixels[3 * i + 1] = g;
        pixels[3 * i + 2] = r;
    }
}

/**
 * Destructor
 */
Image::~Image() {}

/**
 * This method returns the height of an image.
 */
u_int32_t Image::getHeight() const { return height; }

/**
 * This method returns the width of an image.
 */
u_int32_t Image::getWidth() const { return width; }

/**
 * This method returns the pixels of an image.
 */
std::vector<uint8_t> Image::getPixels() const { return pixels; }

/**
 * This method writes the content of an image to a .bmp file. At the
 * moment all files are created with Bitmap version V3.
 */
void Image::writeImageToFile(const std::filesystem::path filePath)
{
    std::ofstream output(filePath, std::ofstream::binary);

    BitmapFileHeader fileHeader;
    fileHeader.headerFieldA = 'B';
    fileHeader.headerFieldB = 'M';
    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + pixels.size();
    fileHeader.reservedA = 0;
    fileHeader.reservedB = 0;
    fileHeader.imageOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    output.write(reinterpret_cast<char *>(&fileHeader), sizeof(BitmapFileHeader));

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
    output.write(reinterpret_cast<char *>(&infoHeader), sizeof(BitmapInfoHeader));
    uint32_t rowSize = ((width * 3 + 3) / 4) * 4;
    for (int i = 0; i < height; i++)
    {
        output.write(reinterpret_cast<char *>(&pixels[i * rowSize]), rowSize);
    }
}