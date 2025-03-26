
# LED Color Evolution

**LED Color Evolution** is an interactive light-based project that runs on a 64×64 RGB LED matrix cube. It uses evolutionary algorithms to gradually morph the matrix display into a target image—pixel by pixel—creating a mesmerizing visual narrative of convergence, mutation, and transformation.

This project is based on and extends functionality from the [rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix) library, which was cloned as a base to drive the hardware display. From there, I developed custom animation demos using both **genetic algorithms** and **guided mutation** strategies.

![Alt text](data/cube_to_cloud.gif)

![Alt text](data/cube_to_grid.gif)

---

## Features

- Evolves pixel colors toward a target image
- Two custom demos: GeneticColorEvolution and GuidedColorEvolution
- Loads and scales images using **GraphicsMagick++**
- Compatible with Raspberry Pi + LED matrix hardware
- Includes **GoogleTest** unit tests for core functions

---


### Prerequisites

- C++17 compiler (e.g. `g++-11+`)
- CMake ≥ 3.10
- [GraphicsMagick++](https://www.graphicsmagick.org/)
- Raspberry Pi-compatible RGB LED matrix
- (Optional) GoogleTest for unit testing

### Hardware Setup
Power: Ensure both the DC power jack and USB-C are connected.

Raspberry Pi hostname: m0therb0ardd@raspberrypi

### Clone & Build

```bash
git clone https://github.com/m0therb0ardd/my-led-evolution.git
cd my-led-evolution
mkdir build && cd build
cmake ..
cmake --build .
```
### Software and Compilation
    When using make, you must specify the hardware description to match your LED HAT.
```bash
make image-example HARDWARE_DESC=adafruit-hat-pwm
```

### Transferring Files from Local to RPi
Use scp to copy image files from your local computer to your Raspberry Pi:
```bash
scp grid.png m0therb0ardd@raspberrypi:/home/m0therb0ardd/rpi-rgb-led-matrix/examples-api-use/
```

### Image COnversion PNG -> PPM
Use convert (from ImageMagick or GraphicsMagick) to resize and convert your image:
```bash
convert grid.png -resize 64x64! -depth 8 -colorspace RGB grid.ppm
```

### Run Custom Color Evolution Demo

```bash
sudo ./demo --led-rows=64 --led-cols=64 --led-chain=1 --led-parallel=1 -D 10 grid.ppm

    -D 10 = GuidedColorEvolution

    -D 11 = GeneticColorEvolution
```
Make sure grid.ppm is your target image and that its dimensions match your matrix layout (64x64 in this case).

### Running Tests
```bash
cmake --build . --target run_tests
ctest --output-on-failure
```
You can also run all tests directly with:
```bash
./run_tests
```
