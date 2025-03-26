/**
 * @file shared.cpp
 * @brief Contains shared global variables and image loading utilities
 *        for LED matrix demos.
 */

#include "shared.h"
#include <iostream>

/// Global vector that stores the RGB values for the target image pixels.
std::vector<uint32_t> targetPixels;

/// Global flag that is set to true when a termination signal is received.
volatile bool interrupt_received = false;

/**
 * @brief Loads and scales an image to the given matrix dimensions.
 *
 * Uses GraphicsMagick to load a static image or first frame of a GIF, and
 * resizes it to the target dimensions (e.g., 64x64) for display on the LED matrix.
 *
 * @param filename Path to the image file to load.
 * @param target_width Desired output width in pixels.
 * @param target_height Desired output height in pixels.
 * @return ImageVector Vector of Magick::Image objects. Returns an empty vector on error.
 */
ImageVector LoadImageAndScaleImage(const char *filename,
                                   int target_width,
                                   int target_height) {
  ImageVector result;
  ImageVector frames;

  try {
    readImages(&frames, filename);  ///< Loads frames from image file
  } catch (std::exception &e) {
    std::cerr << "Error loading image: " << e.what() << std::endl;
    return result;
  }

  if (frames.empty()) {
    std::cerr << "No image found in " << filename << "." << std::endl;
    return result;
  }

  result.push_back(frames[0]);  ///< Use the first frame only (good for static or GIF)
  result[0].scale(Magick::Geometry(target_width, target_height));  ///< Resize image to match matrix
  return result;
}
