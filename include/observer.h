#ifndef INCLUDE_OBSERVER_H_
#define INCLUDE_OBSERVER_H_

#include "direction.h"
#include "wave.h"

class Observer {
  private:
    // Size of the wave
    const std::size_t row, col, size;

    // Number of patterns
    const std::size_t num_patterns;

    // Compatibility matrix for patterns
    const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
        compatibility;

    // Number of compatibile patterns in each direction
    std::vector<std::vector<std::array<std::size_t, NUM_DIRECTIONS>>>
        compatibility_count;

    // Queue of observed cells
    std::vector<std::pair<std::size_t, std::size_t>> queue;

  public:
    // Initialize observer
    Observer(
        std::size_t row, std::size_t col,
        const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
            &compatibility);

    // Remove pattern from the wave
    void remove_pattern(std::size_t index, std::size_t pattern);

    // Remove pattern from the wave
    void remove_pattern(std::size_t i, std::size_t j, std::size_t pattern);

    // Propagate the observation
    void propagate(Wave &wave);
};

#endif