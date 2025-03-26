#ifndef GUIDED_EVOLUTION_H
#define GUIDED_EVOLUTION_H

#include "demo_runner.h"
#include <vector>
#include <cstdint>

extern std::vector<uint32_t> targetPixels;

class GuidedColorEvolution : public DemoRunner {
public:
    GuidedColorEvolution(rgb_matrix::Canvas* canvas, int delay_ms = 50);
    void Run() override;

private:
    void guidedMutate(uint32_t& color, uint32_t target, int step = 1);

    std::vector<uint32_t> pixels_;
    int width_, height_, popSize_;
    int delay_ms_;
};

#endif // GUIDED_EVOLUTION_H
