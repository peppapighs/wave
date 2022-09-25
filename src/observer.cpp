#include "observer.h"
#include "direction.h"
#include "wave.h"

#include <tuple>

Observer::Observer(
    std::size_t row, std::size_t col,
    const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
        &compatibility)
    : row(row), col(col), size(row * col), num_patterns(compatibility.size()),
      compatibility(compatibility),
      compatibility_count(
          size,
          std::vector<std::array<std::size_t, NUM_DIRECTIONS>>(num_patterns)) {
    for (std::size_t i = 0; i < size; i++)
        for (std::size_t pattern = 0; pattern < num_patterns; pattern++)
            for (std::size_t direction = 0; direction < NUM_DIRECTIONS;
                 direction++)
                compatibility_count[i][pattern][direction] =
                    compatibility[pattern][direction].size();
}

void Observer::remove_pattern(std::size_t index, std::size_t pattern) {
    compatibility_count[index][pattern].fill(0);
    queue.emplace_back(index, pattern);
}

void Observer::remove_pattern(std::size_t i, std::size_t j,
                              std::size_t pattern) {
    remove_pattern(i * col + j, pattern);
}

void Observer::propagate(Wave &wave) {
    while (!queue.empty()) {
        std::size_t index, pattern;
        std::tie(index, pattern) = queue.back();
        queue.pop_back();

        long r = index / col, c = index % col;
        for (std::size_t i = 0; i < NUM_DIRECTIONS; i++) {
            long nr = r + DX[i], nc = c + DY[i];

            if (nr < 0 || nr >= row || nc < 0 || nc >= col)
                continue;

            std::size_t nindex = nr * col + nc;
            for (const std::size_t &pattern : compatibility[pattern][i]) {
                --compatibility_count[nindex][pattern][OPPOSITE[i]];

                if (compatibility_count[nindex][pattern][OPPOSITE[i]] == 0) {
                    remove_pattern(nindex, pattern);
                    wave.remove_pattern(nindex, pattern);
                }
            }
        }
    }
}