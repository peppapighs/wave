#include "direction.h"
#include "generator.h"

#include <array>
#include <iostream>
#include <memory>
#include <vector>

const int SEED = 42;
const std::size_t ROW = 10;
const std::size_t COL = 30;
const std::size_t NUM_PATTERNS = 12;

const std::vector<std::string> PATTERNS = {" ", "═", "║", "╔", "╗", "╚",
                                           "╝", "╠", "╣", "╦", "╩", "╬"};
const std::vector<double> WEIGHTS = {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const std::vector<std::array<bool, NUM_DIRECTIONS>> EDGES = {
    {0, 0, 0, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}, {1, 1, 0, 0},
    {1, 0, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 0},
    {1, 0, 1, 1}, {1, 1, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}};

std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
    compatibility(NUM_PATTERNS);

int main(int argc, char **argv) {
    for (std::size_t i = 0; i < NUM_PATTERNS; i++)
        for (std::size_t direction = 0; direction < NUM_DIRECTIONS;
             direction++) {
            compatibility[i][direction] = {};
            for (std::size_t j = 0; j < NUM_PATTERNS; j++)
                if (EDGES[i][direction] == EDGES[j][OPPOSITE[direction]])
                    compatibility[i][direction].emplace_back(j);
        }

    std::unique_ptr<Generator> generator =
        std::make_unique<Generator>(SEED, ROW, COL, WEIGHTS, compatibility);

    std::vector<std::size_t> patterns = generator->generate();
    if (patterns.empty()) {
        std::cerr << "Failed to generate a maze." << std::endl;
        return 1;
    }

    for (std::size_t i = 0; i < ROW; i++) {
        for (std::size_t j = 0; j < COL; j++)
            std::cout << PATTERNS[patterns[i * COL + j]];
        std::cout << std::endl;
    }

    return 0;
}