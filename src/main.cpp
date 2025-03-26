
#include <iostream>     // for std::cout, std::cerr
#include <csignal>      // for signal(), SIGINT, SIGTERM
#include <getopt.h>     // for getopt(), optarg, optind
#include <memory>       // for std::unique_ptr
#include <cstdlib>      // for atoi()
#include <Magick++.h>   // for Magick::InitializeMagick

#include "led-matrix.h"         // for RGBMatrix, Canvas
#include "demo_runner.h"        // for DemoRunner base class
#include "guided_evolution.h"   // your GuidedColorEvolution
#include "genetic_colors.h"     // your GeneticColors
#include "shared.h"             // shared state, image loader

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

void InterruptHandler(int signo) {
  interrupt_received = true;
}

int usage(const char* progname) {
  std::cerr << "Usage: " << progname << " -D <demo> [options]\n";
  return 1;
}


int main(int argc, char *argv[]) {
  Magick::InitializeMagick(*argv);  // Initialize GraphicsMagick

  int scroll_ms = 30;
  int demo = -1;
  const char *demo_parameter = NULL;

  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;
  matrix_options.rows = 32;
  matrix_options.chain_length = 1;
  matrix_options.parallel = 1;

  // Parse matrix options
  if (!ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
    return usage(argv[0]);
  }

  // Parse command-line options
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

  // Create LED matrix
  auto matrix = std::unique_ptr<RGBMatrix>(
      RGBMatrix::CreateFromOptions(matrix_options, runtime_opt));

  if (!matrix) {
    std::cerr << TERM_ERR << "Failed to initialize matrix.\n" << TERM_NORM;
    return 1;
  }

  Canvas *canvas = matrix.get();

  // Load and scale the image (first frame for now, but supports GIF later)
  ImageVector images = LoadImageAndScaleImage(
      demo_parameter, matrix->width(), matrix->height());

  if (images.empty()) {
    std::cerr << TERM_ERR << "Failed to load target image.\n" << TERM_NORM;
    return 1;
  }

  // Convert first image to targetPixels
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

  //Create appropriate demo runner
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

  // Set up signal handler to exit on CTRL+C
  signal(SIGINT, InterruptHandler);
  signal(SIGTERM, InterruptHandler);
  std::cout << "Press <CTRL-C> to exit and reset LEDs\n";

  // Run the selected animation
  demo_runner->Run();

  std::cout << "Received CTRL-C. Exiting.\n";
  return 0;
}

