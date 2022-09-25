#ifndef INCLUDE_WAVE_H_
#define INCLUDE_WAVE_H_

#include <random>

// Noise factor for breaking entropy ties
const double NOISE_FACTOR = 1E-6;

class Wave {
  private:
    // Size of the wave
    const std::size_t row, col, size;

    // Number of patterns
    const std::size_t num_patterns;

    // Pattern weights
    const std::vector<double> weights;

    // Pattern w * log(w)
    const std::vector<double> w_log_w;

    // Wave data (0 - can place a pattern, 1 - cannot place a pattern)
    std::vector<std::vector<bool>> data;

    // Sum of weights
    std::vector<double> sum_weights;

    // Sum of w * log(w)
    std::vector<double> sum_w_log_w;

    // Entropy of the wave
    std::vector<double> entropy;

    // Number of remaining patterns in the wave
    std::vector<std::size_t> remaining_patterns;

  public:
    // Initialize wave
    Wave(std::size_t row, std::size_t col, const std::vector<double> &weights);

    // Remove pattern from the wave
    void remove_pattern(std::size_t index, std::size_t pattern);

    // Remove pattern from the wave
    void remove_pattern(std::size_t i, std::size_t j, std::size_t pattern);

    // Get the index of the cell with minimum entropy
    // Return -1 if no cell is available
    long get_min_entropy(std::mt19937 &rng) const;

    // Return true if the wave is impossible to solve
    bool is_impossible() const;
};

#endif