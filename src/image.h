#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <vector>
#include <filesystem>
#include "bitmap.h"

class Image
{
public:
    Image(uint32_t width, uint32_t height);
    Image(const Image &other);
    Image(const std::filesystem::path imagePath);
    Image(uint32_t width, uint32_t height, uint8_t r, uint8_t g, uint8_t b);
    ~Image();

    uint32_t getWidth();
    uint32_t getHeight();
    void writeImageToFile(const std::filesystem::path filePath);

private:
    uint32_t width;
    uint32_t height;
    std::vector<uint8_t> pixels;
};

#endif