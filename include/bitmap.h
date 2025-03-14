#pragma once

#include <cstdint>

#pragma pack(1)

/**
 * @struct BitmapFileHeader
 *
 * @brief Struct representing the header of a bitmap file.
 *
 */
struct BitmapFileHeader {
    /**
     * @brief Must be 'B'.
     *
     */
    uint8_t headerFieldA;
    /**
     * @brief Must be 'M'.
     *
     */
    uint8_t headerFieldB;
    /**
     * @brief File header + info header + pixel array.
     *
     */
    uint32_t fileSize;
    /**
     * @brief Can be used by an application, default 0.
     *
     */
    uint16_t reservedA;
    /**
     * @brief Can be used by an application, default 0.
     *
     */
    uint16_t reservedB;
    /**
     * @brief Starting location of the pixel array.
     *
     */
    uint32_t imageOffset;
};

/**
 * @struct BitmapInfoHeader
 *
 * @brief Struct for V3 bitmap info header.
 *
 */
struct BitmapInfoHeader {
    /**
     * @brief Size of this struct.
     *
     */
    uint32_t headerSize;
    /**
     * @brief Image width.
     *
     */
    int32_t bitmapWidth;
    /**
     * @brief Image height.
     *
     */
    int32_t bitmapHeight;
    /**
     * @brief Must be 1.
     *
     */
    uint16_t numberOfColorPlanes;
    /**
     * @brief 24 for RGB, 8 for greyscale, 1 for mono.
     *
     */
    uint16_t bitsPerPixel;
    /**
     * @brief No compression, therefore always 0.
     *
     */
    uint32_t compressionMethod;
    /**
     * @brief Can be ignored if there is no compression.
     *
     */
    uint32_t imageSize;
    /**
     * @brief Can be ignored.
     *
     */
    int32_t horizontalResolution;
    /**
     * @brief Can be ignored.
     *
     */
    int32_t verticalResolution;
    /**
     * @brief Number of colors, 0 for 2^n default.
     *
     */
    uint32_t colorPalette;
    /**
     * @brief 0, if all colors are important.
     *
     */
    uint32_t importantColors;
};

#pragma pack()