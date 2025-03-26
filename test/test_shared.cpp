#include <gtest/gtest.h>
#include "shared.h"

//tests that LoadImageandScaleImage actually load something 
TEST(SharedImageTest, LoadImageReturnsNonEmptyVector) {
  auto images = LoadImageAndScaleImage("test.ppm", 64, 64);
  EXPECT_FALSE(images.empty());
}
