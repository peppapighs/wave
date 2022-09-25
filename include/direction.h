#ifndef INCLUDE_DIRECTION_H_
#define INCLUDE_DIRECTION_H_

#include <array>

const std::size_t NUM_DIRECTIONS = 4;

const std::array<int, NUM_DIRECTIONS> DX = {1, 0, -1, 0};

const std::array<int, NUM_DIRECTIONS> DY = {0, 1, 0, -1};

const std::array<std::size_t, NUM_DIRECTIONS> OPPOSITE = {2, 3, 0, 1};

#endif