#include "shared.h"
#include <iostream>

std::vector<uint32_t> targetPixels;
volatile bool interrupt_received = false;

ImageVector LoadImageAndScaleImage(const char *filename,
                                   int target_width,
                                   int target_height) {
  ImageVector result;
  ImageVector frames;

  try {
    readImages(&frames, filename);  // Magick function
  } catch (std::exception &e) {
    std::cerr << "Error loading image: " << e.what() << std::endl;
    return result;
  }

  if (frames.empty()) {
    std::cerr << "No image found in " << filename << "." << std::endl;
    return result;
  }

  result.push_back(frames[0]);
  result[0].scale(Magick::Geometry(target_width, target_height));
  return result;
}
