#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <vector>

typedef struct {
    uint32_t width;
    uint32_t height;
    std::vector<char> pixels; // pixels are stored B G R B G R B G R ...
} Image;

#endif