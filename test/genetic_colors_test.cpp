#include <gtest/gtest.h>
#include "genetic_colors.h"  // use quotes since it's in include/
#include "shared.h"          // required for targetPixels if used in future

TEST(ColorUtilsTest, RGBExtraction) {
    int color = 0x123456;
    EXPECT_EQ((color >> 16) & 0xFF, 0x12);
    EXPECT_EQ((color >> 8) & 0xFF, 0x34);
    EXPECT_EQ(color & 0xFF, 0x56);
}

TEST(FitnessTest, IdenticalColors) {
    int color1 = 0x123456;
    int color2 = 0x123456;
    EXPECT_EQ(GeneticColors::calcFitness(color1, color2), 0);
}

TEST(FitnessTest, DifferentColors) {
    int color1 = 0x000000;
    int color2 = 0xFFFFFF;
    int fitness = GeneticColors::calcFitness(color1, color2);
    EXPECT_GT(fitness, 0);
}
