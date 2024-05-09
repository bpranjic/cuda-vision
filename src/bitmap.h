#ifndef BITMAP_H
#define BITMAP_H
#include <cstdint>

#pragma pack(1) // remove padding

typedef struct {
    uint8_t headerFieldA; // has to be 'B'
    uint8_t headerFieldB; // has to be 'M'
    uint32_t fileSize; // File header + info header + pixel array
    uint16_t reservedA; // can be used by application, default 0
    uint16_t reservedB; // can be used by application, default 0
    uint32_t imageOffset; // starting location of pixel array
} BitmapFileHeader;

typedef struct {
    uint32_t headerSize; // size of this struct
    int32_t bitmapWidth; // image width
    int32_t bitmapHeight; // image height
    uint16_t numberOfColorPlanes; // always has to be 1
    uint16_t bitsPerPixel; // 24 for RGB, 8 for greyscale, 1 for mono
    uint32_t compressionMethod; // no compression so always 0
    uint32_t imageSize; // can be ignored when no compression
    int32_t horizontalResolution; // can be ignored
    int32_t verticalResolution; // can be ignores
    uint32_t colorPalette; // number of colors, 0 for 2^n default
    uint32_t importantColors; // 0 if all colors are important
} BitmapInfoHeader;

#pragma pack() // restore padding for other header files
#endif