#pragma once

#include <Magick++.h>
#include <vector>
#include <cstdint>  // for uint32_t

using ImageVector = std::vector<Magick::Image>;

// Terminal formatting macros
#define TERM_ERR  "\033[1;31m"
#define TERM_NORM "\033[0m"

// Global pixel target data
extern std::vector<uint32_t> targetPixels;

// Graceful interrupt signal
extern volatile bool interrupt_received;
void InterruptHandler(int signo);

// Image loader
ImageVector LoadImageAndScaleImage(const char *filename,
                                   int target_width,
                                   int target_height);
