#ifndef GENETIC_COLORS_H
#define GENETIC_COLORS_H

#include "demo_runner.h"
#include <vector>
#include <cstdint>

extern std::vector<uint32_t> targetPixels;

class GeneticColors : public DemoRunner {
public:
    GeneticColors(rgb_matrix::Canvas* canvas, int delay_ms = 200);
    void Run() override;

    static int calcFitness(int value, int target);

private:
    struct citizen {
        int dna = 0;
    };

    std::vector<citizen> parents_, children_;
    int width_, height_, popSize_;
    int delay_ms_;

    static int randColor();
    static int R(int color);
    static int G(int color);
    static int B(int color);

    void sortByFitness();
    void mate();
    void guidedMutate(citizen& c, uint32_t target, int step = 1);
    void showTargetImage();
    void swapGenerations();
    bool is85PercentFit();
};

#endif // GENETIC_COLORS_H
