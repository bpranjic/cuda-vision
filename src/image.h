#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <vector>
#include <filesystem>
#include "bitmap.h"

/**
 * @class Image
 * @brief A class to represent and manipulate images.
 */
class Image
{
public:
    /**
     * @brief Constructor to create an empty image with given width and height.
     * @param width Width of the image.
     * @param height Height of the image.
     */
    Image(uint32_t width, uint32_t height);

    /**
     * @brief Constructor to create an image with given width, height, and pixel data.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param pixels Vector containing the pixel data.
     */
    Image(uint32_t width, uint32_t height, std::vector<uint8_t> pixels);

    /**
     * @brief Copy constructor to create a copy of an existing image.
     * @param other The image to be copied.
     */
    Image(const Image &other);

    /**
     * @brief Constructor to create an image from a file.
     * @param imagePath The file path of the image to be loaded.
     */
    Image(const std::filesystem::path imagePath);

    /**
     * @brief Constructor to create an image with a solid color.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param r Red component of the color.
     * @param g Green component of the color.
     * @param b Blue component of the color.
     */
    Image(uint32_t width, uint32_t height, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Destructor for the Image class.
     */
    ~Image();

    /**
     * @brief Get the width of the image.
     * @return Width of the image.
     */
    uint32_t getWidth() const;

    /**
     * @brief Get the height of the image.
     * @return Height of the image.
     */
    uint32_t getHeight() const;

    /**
     * @brief Get the pixel data of the image.
     * @return Vector containing the pixel data.
     */
    std::vector<uint8_t> getPixels() const;

    /**
     * @brief Write the image to a file.
     * @param filePath The file path where the image will be saved.
     */
    void writeImageToFile(const std::filesystem::path filePath);

private:
    uint32_t width;
    uint32_t height;
    std::vector<uint8_t> pixels;
};

#endif // IMAGE_H
