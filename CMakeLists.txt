

cmake_minimum_required(VERSION 3.14)
project(my_led_evolution)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -O3 -g -Wextra -Wno-unused-parameter)

# Find GraphicsMagick++
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMAGICK REQUIRED GraphicsMagick++)

# Include headers
include_directories(
  ${GMAGICK_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/matrix/include  # <- this is key
)

# Your source files
add_library(PROJECT_SOURCES
  src/genetic_colors.cpp
  src/guided_evolution.cpp
  src/shared.cpp
)

add_executable(main_exec src/main.cpp)

target_link_libraries(main_exec
  ${GMAGICK_LIBRARIES}
  GraphicsMagick       # <- ADD THIS LINE explicitly
  ${CMAKE_SOURCE_DIR}/matrix/lib/librgbmatrix.a
  PROJECT_SOURCES
  pthread
  rt
  m
)

# ---- Google Test ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Add test directory
add_subdirectory(test)
enable_testing()
