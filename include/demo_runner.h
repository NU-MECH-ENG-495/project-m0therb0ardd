#ifndef DEMO_RUNNER_H
#define DEMO_RUNNER_H

#include "led-matrix.h"  // For rgb_matrix::Canvas

/**
 * @brief Abstract base class for all LED matrix demos.
 * 
 * Subclasses must implement the Run() method to animate on the matrix.
 */
class DemoRunner {
protected:
    explicit DemoRunner(rgb_matrix::Canvas* canvas) : canvas_(canvas) {}
    inline rgb_matrix::Canvas* canvas() { return canvas_; }

public:
    virtual ~DemoRunner() = default;
    virtual void Run() = 0;

private:
    rgb_matrix::Canvas* const canvas_;  // Immutable pointer to canvas
};

#endif // DEMO_RUNNER_H
