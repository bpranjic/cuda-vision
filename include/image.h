#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

#include "bitmap.h"

using namespace std;
namespace fs = std::filesystem;

/**
 * @class Image
 *
 * @brief A class to represent and manipulate images.
 *
 */
class Image {
   public:
    /**
     * @brief Constructor to create an empty image with given width and height.
     *
     * @param width Width of the image.
     * @param height Height of the image.
     *
     */
    Image(unsigned int width, unsigned int height) : width(width), height(height) {};

    /**
     * @brief Constructor to create an image with given width, height, and pixel data.
     *
     * @param width Width of the image.
     * @param height Height of the image.
     * @param pixels Vector containing the pixel data.
     *
     */
    Image(unsigned int width, unsigned height, vector<unsigned char> pixels)
        : width(width), height(height), pixels(pixels) {};

    /**
     * @brief Copy constructor to create a copy of an existing image.
     *
     * @param other The image to be copied.
     *
     */
    Image(const Image& other) : width(other.width), height(other.height), pixels(other.pixels) {};

    /**
     * @brief Constructor to create an image from a file.
     *
     * @param imagePath The file path of the image to be loaded.
     *
     */
    Image(const fs::path imagePath);

    /**
     * @brief Constructor to create an image with a solid color.
     *
     * @param width Width of the image.
     * @param height Height of the image.
     * @param r Red component of the color.
     * @param g Green component of the color.
     * @param b Blue component of the color.
     *
     */
    Image(unsigned int width, unsigned int height, unsigned char r, unsigned char g,
          unsigned char b);

    /**
     * @brief Destructor for the Image class.
     *
     */
    ~Image() {};

    /**
     * @brief Get the width of the image.
     *
     * @return Width of the image.
     *
     */
    unsigned int getWidth() const;

    /**
     * @brief Get the height of the image.
     *
     * @return Height of the image.
     *
     */
    unsigned int getHeight() const;

    /**
     * @brief Get the pixel data of the image.
     *
     * @return Vector containing the pixel data.
     *
     */
    vector<unsigned char> getPixels() const;

    /**
     * @brief Write the image to a file.
     *
     * @param filePath The file path where the image will be saved.
     *
     */
    void writeImageToFile(const fs::path filePath);

   private:
    unsigned int width;
    unsigned int height;
    vector<unsigned char> pixels;
};
