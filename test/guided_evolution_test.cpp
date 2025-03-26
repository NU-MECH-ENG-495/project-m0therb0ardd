#include <gtest/gtest.h>
#include "guided_evolution.h"

TEST(GuidedEvolutionTest, IdenticalColorsHaveZeroFitness) {
    EXPECT_EQ(GuidedColorEvolution::calcFitness(0xABCDEF, 0xABCDEF), 0);
}

TEST(GuidedEvolutionTest, VeryDifferentColorsHaveHighFitness) {
    EXPECT_GT(GuidedColorEvolution::calcFitness(0x000000, 0xFFFFFF), 700);
}
