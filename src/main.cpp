/**
 * @file main.cpp
 * @brief Main entry point for running LED matrix evolution demos.
 *
 * This file initializes the LED matrix, loads a target image,
 * and launches the selected demo animation (e.g., guided or genetic evolution).
 */

#include <iostream>
#include <csignal>
#include <getopt.h>
#include <memory>
#include <cstdlib>
#include <Magick++.h>

#include "led-matrix.h"
#include "demo_runner.h"
#include "guided_evolution.h"
#include "genetic_colors.h"
#include "shared.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

/**
 * @brief Signal handler to catch interrupt signals and set termination flag.
 * 
 * @param signo The signal number received.
 */
void InterruptHandler(int signo) {
  interrupt_received = true;
}

/**
 * @brief Prints usage instructions for this program.
 * 
 * @param progname The name of the executable.
 * @return int Always returns 1 to indicate incorrect usage.
 */
int usage(const char* progname) {
  std::cerr << "Usage: " << progname << " -D <demo> [options]\n";
  return 1;
}

/**
 * @brief Entry point of the program.
 * 
 * Parses command-line arguments, loads the target image, creates the LED matrix,
 * and runs the specified demo (guided or genetic color evolution).
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit code.
 */
int main(int argc, char *argv[]) {
  Magick::InitializeMagick(*argv);  ///< Initialize ImageMagick

  int scroll_ms = 30;
  int demo = -1;
  const char *demo_parameter = NULL;

  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;
  matrix_options.rows = 32;
  matrix_options.chain_length = 1;
  matrix_options.parallel = 1;

  // Parse matrix-related command-line flags
  if (!ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
    return usage(argv[0]);
  }

  // Parse demo-specific command-line options
  int opt;
  while ((opt = getopt(argc, argv, "dD:r:P:c:p:b:m:LR:")) != -1) {
    switch (opt) {
      case 'D': demo = atoi(optarg); break;
      case 'm': scroll_ms = atoi(optarg); break;
      default: return usage(argv[0]);
    }
  }

  if (optind < argc) {
    demo_parameter = argv[optind];
  }

  if (demo < 0) {
    std::cerr << TERM_ERR << "Expected required option -D <demo>\n" << TERM_NORM;
    return usage(argv[0]);
  }

  // Create the LED matrix object
  auto matrix = std::unique_ptr<RGBMatrix>(
      RGBMatrix::CreateFromOptions(matrix_options, runtime_opt));
  if (!matrix) {
    std::cerr << TERM_ERR << "Failed to initialize matrix.\n" << TERM_NORM;
    return 1;
  }

  Canvas *canvas = matrix.get();

  // Load the target image (1st frame if it's a GIF)
  ImageVector images = LoadImageAndScaleImage(
      demo_parameter, matrix->width(), matrix->height());

  if (images.empty()) {
    std::cerr << TERM_ERR << "Failed to load target image.\n" << TERM_NORM;
    return 1;
  }

  // Convert image to list of target pixel values
  const Magick::Image &targetImage = images[0];
  targetPixels.clear();
  for (size_t y = 0; y < targetImage.rows(); ++y) {
    for (size_t x = 0; x < targetImage.columns(); ++x) {
      const Magick::Color &c = targetImage.pixelColor(x, y);
      uint32_t rgb = (ScaleQuantumToChar(c.redQuantum()) << 16) |
                     (ScaleQuantumToChar(c.greenQuantum()) << 8) |
                     ScaleQuantumToChar(c.blueQuantum());
      targetPixels.push_back(rgb);
    }
  }

  if (targetPixels.size() != matrix->width() * matrix->height()) {
    std::cerr << TERM_ERR << "ERROR: targetPixels size (" 
              << targetPixels.size() << ") does not match matrix size ("
              << matrix->width() * matrix->height() << ")\n" << TERM_NORM;
    return 1;
  }

  // Instantiate the appropriate animation demo
  std::unique_ptr<DemoRunner> demo_runner;
  switch (demo) {
    case 10:
      demo_runner = std::make_unique<GuidedColorEvolution>(canvas, scroll_ms);
      break;
    case 11:
      demo_runner = std::make_unique<GeneticColors>(canvas, scroll_ms);
      break;
    default:
      return usage(argv[0]);
  }

  if (!demo_runner) {
    return usage(argv[0]);
  }

  // Set up signal handlers to allow safe exit on Ctrl+C
  signal(SIGINT, InterruptHandler);
  signal(SIGTERM, InterruptHandler);
  std::cout << "Press <CTRL-C> to exit and reset LEDs\n";

  // Run the selected demo animation
  demo_runner->Run();

  std::cout << "Received CTRL-C. Exiting.\n";
  return 0;
}
