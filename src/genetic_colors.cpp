#include "genetic_colors.h"
#include "shared.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>

GeneticColors::GeneticColors(rgb_matrix::Canvas* canvas, int delay_ms)
    : DemoRunner(canvas), delay_ms_(delay_ms) {
    width_ = canvas->width();
    height_ = canvas->height();
    popSize_ = width_ * height_;
    children_.resize(popSize_);
    parents_.resize(popSize_);
    std::srand(std::time(nullptr));
}

void GeneticColors::Run() {
    for (int i = 0; i < popSize_; ++i)
        children_[i].dna = randColor();
    parents_ = children_;
    showTargetImage();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (!interrupt_received) {
        swapGenerations();
        sortByFitness();
        mate();

        for (int i = 0; i < popSize_; ++i) {
            const auto& c = children_[i];
            int x = i % width_;
            int y = i / width_;
            canvas()->SetPixel(x, y, R(c.dna), G(c.dna), B(c.dna));
        }

        if (is85PercentFit()) {
            for (int i = 0; i < popSize_; ++i)
                guidedMutate(children_[i], targetPixels[i], 5);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms_));
    }
}

int GeneticColors::randColor() { return rand() & 0xFFFFFF; }

int GeneticColors::calcFitness(int value, int target) {
    int dr = R(value) - R(target);
    int dg = G(value) - G(target);
    int db = B(value) - B(target);
    return dr * dr + dg * dg + db * db;
}

void GeneticColors::sortByFitness() {
    std::vector<std::pair<int, citizen>> indexed;
    indexed.reserve(popSize_);
    for (int i = 0; i < popSize_; ++i)
        indexed.emplace_back(i, parents_[i]);

    std::sort(indexed.begin(), indexed.end(),
        [](const auto& a, const auto& b) {
            return calcFitness(a.second.dna, targetPixels[a.first]) <
                   calcFitness(b.second.dna, targetPixels[b.first]);
        });

    for (int i = 0; i < popSize_; ++i)
        parents_[i] = indexed[i].second;
}

void GeneticColors::mate() {
    constexpr float eliteRate = 0.1f;
    constexpr float mutationRate = 0.5f;
    int eliteCount = static_cast<int>(popSize_ * eliteRate);

    for (int i = 0; i < eliteCount; ++i)
        children_[i] = parents_[i];

    for (int i = eliteCount; i < popSize_; ++i) {
        children_[i] = parents_[i];
        if ((rand() / static_cast<float>(RAND_MAX)) < mutationRate)
            guidedMutate(children_[i], targetPixels[i], 5);
    }
}

void GeneticColors::guidedMutate(citizen& c, uint32_t target, int step) {
    int r = R(c.dna), g = G(c.dna), b = B(c.dna);
    int tr = R(target), tg = G(target), tb = B(target);

    r = (r < tr) ? std::min(255, r + step) : std::max(0, r - step);
    g = (g < tg) ? std::min(255, g + step) : std::max(0, g - step);
    b = (b < tb) ? std::min(255, b + step) : std::max(0, b - step);

    c.dna = (r << 16) | (g << 8) | b;
}

void GeneticColors::showTargetImage() {
    for (int i = 0; i < popSize_; ++i) {
        int x = i % width_;
        int y = i / width_;
        uint32_t rgb = targetPixels[i];
        canvas()->SetPixel(x, y, R(rgb), G(rgb), B(rgb));
    }
}

void GeneticColors::swapGenerations() {
    std::swap(parents_, children_);
}

bool GeneticColors::is85PercentFit() {
    int fitCount = 0;
    for (int i = 0; i < popSize_; ++i) {
        if (calcFitness(children_[i].dna, targetPixels[i]) < 1)
            ++fitCount;
    }
    return (fitCount / static_cast<float>(popSize_)) > 0.85f;
}

int GeneticColors::R(int color) { return (color >> 16) & 0xFF; }
int GeneticColors::G(int color) { return (color >> 8) & 0xFF; }
int GeneticColors::B(int color) { return color & 0xFF; }
