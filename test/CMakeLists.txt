add_executable(unit_test
  genetic_colors_test.cpp
  guided_evolution_test.cpp
  test_shared.cpp
  ${CMAKE_SOURCE_DIR}/src/shared.cpp
)

target_include_directories(unit_test PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(unit_test
  gtest_main
  ${GMAGICK_LIBRARIES}
  pthread
)

include(GoogleTest)
gtest_discover_tests(unit_test)
