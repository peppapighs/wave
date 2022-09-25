#ifndef INCLUDE_GENERATOR_H_
#define INCLUDE_GENERATOR_H_

#include "observer.h"
#include "wave.h"

#include <optional>

class Generator {
  private:
    // Size of the wave
    const std::size_t row, col, size;

    // Number of patterns
    const std::size_t num_patterns;

    // Pattern weights
    const std::vector<double> weights;

    // Random engine
    std::mt19937 rng;

    // Wave
    Wave wave;

    // Observer
    Observer observer;

  public:
    // Observe status
    enum class ObserveStatus {
        DONE,     // Successfully observed, finished
        CONTINUE, // Successfully observed, continue
        FAILED    // Failed to observe
    };

    // Initialize generator
    Generator(
        std::size_t row, std::size_t col, const std::vector<double> &weights,
        const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
            &compatibility);

    // Initialize generator
    Generator(
        int seed, std::size_t row, std::size_t col,
        const std::vector<double> &weights,
        const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
            &compatibility);

    // Observe a cell with lowest entropy
    ObserveStatus observe();

    // Generate patterns from Wave Function Collapse algorithm
    // Return empty vector if failed
    std::vector<std::size_t> generate();
};

#endif