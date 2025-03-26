/**
 * @file guided_evolution.cpp
 * @brief Implements GuidedColorEvolution, a class that smoothly transitions pixel colors to match a target image.
 */

#include "guided_evolution.h"
#include "shared.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

/**
 * @brief Constructs a GuidedColorEvolution object.
 * 
 * Initializes the canvas and fills the pixel array with random 24-bit RGB colors.
 * 
 * @param canvas Pointer to the LED matrix canvas.
 * @param delay_ms Delay in milliseconds between frames.
 */
GuidedColorEvolution::GuidedColorEvolution(rgb_matrix::Canvas* canvas, int delay_ms)
    : DemoRunner(canvas), delay_ms_(delay_ms) {
    width_ = canvas->width();
    height_ = canvas->height();
    popSize_ = width_ * height_;
    pixels_.resize(popSize_);
    srand(time(NULL));

    for (int i = 0; i < popSize_; ++i) {
        pixels_[i] = rand() & 0xFFFFFF;
    }
}

/**
 * @brief Starts the animation loop which gradually changes pixel colors to match the target image.
 * 
 * The animation stops when all pixels match their respective target values.
 */
void GuidedColorEvolution::Run() {
    while (!interrupt_received) {
        bool allMatch = true;
        for (int i = 0; i < popSize_; ++i) {
            uint32_t target = targetPixels[i];
            guidedMutate(pixels_[i], target);

            int x = i % width_;
            int y = i / width_;
            canvas()->SetPixel(x, y,
                (pixels_[i] >> 16) & 0xFF,
                (pixels_[i] >> 8) & 0xFF,
                pixels_[i] & 0xFF);

            if (pixels_[i] != target) allMatch = false;
        }

        if (allMatch) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms_));
    }
}

/**
 * @brief Gradually mutates a color toward the target color by adjusting RGB channels.
 * 
 * Each color channel is incremented or decremented by a fixed step size
 * until it matches the corresponding target channel.
 * 
 * @param color Reference to the color to be mutated.
 * @param target The target color to evolve toward.
 * @param step The maximum amount each channel can change per frame.
 */
void GuidedColorEvolution::guidedMutate(uint32_t& color, uint32_t target, int step) {
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    int tr = (target >> 16) & 0xFF;
    int tg = (target >> 8) & 0xFF;
    int tb = target & 0xFF;

    if (r < tr) r = std::min(255, r + step);
    else if (r > tr) r = std::max(0, r - step);

    if (g < tg) g = std::min(255, g + step);
    else if (g > tg) g = std::max(0, g - step);

    if (b < tb) b = std::min(255, b + step);
    else if (b > tb) b = std::max(0, b - step);

    color = (r << 16) | (g << 8) | b;
}
