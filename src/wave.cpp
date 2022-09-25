#include "wave.h"

#include <algorithm>

// Compute w * log(w)
std::vector<double> get_w_log_w(const std::vector<double> &weights) {
    std::vector<double> w_log_w;
    for (const double &weight : weights)
        w_log_w.emplace_back(weight * std::log(weight));

    return w_log_w;
}

Wave::Wave(std::size_t row, std::size_t col, const std::vector<double> &weights)
    : row(row), col(col), size(row * col), num_patterns(weights.size()),
      weights(weights), w_log_w(get_w_log_w(weights)),
      data(size, std::vector<bool>(num_patterns)),
      remaining_patterns(size, num_patterns) {
    double base_w = std::accumulate(weights.begin(), weights.end(), 0);
    double base_e = std::accumulate(w_log_w.begin(), w_log_w.end(), 0);
    double base_entropy = std::log(base_w) - base_e / base_w;

    sum_weights = std::vector<double>(size, base_w);
    sum_w_log_w = std::vector<double>(size, base_e);
    entropy = std::vector<double>(size, base_entropy);
}

void Wave::remove_pattern(std::size_t index, std::size_t pattern) {
    if (data[index][pattern])
        return;

    data[index][pattern] = true;
    sum_weights[index] -= weights[pattern];
    sum_w_log_w[index] -= w_log_w[pattern];
    entropy[index] =
        std::log(sum_weights[index]) - sum_w_log_w[index] / sum_weights[index];
    --remaining_patterns[index];
}

void Wave::remove_pattern(std::size_t i, std::size_t j, std::size_t pattern) {
    remove_pattern(i * col + j, pattern);
}

long Wave::get_min_entropy(std::mt19937 &rng) const {
    double min_entropy = std::numeric_limits<double>::max();
    long min_index = -1;

    std::uniform_real_distribution<> dist(0, 1);

    for (std::size_t i = 0; i < size; i++) {
        if (remaining_patterns[i] <= 1)
            continue;

        if (entropy[i] <= min_entropy) {
            double noise = dist(rng) * NOISE_FACTOR;
            if (entropy[i] + noise < min_entropy) {
                min_entropy = entropy[i] + noise;
                min_index = i;
            }
        }
    }

    return min_index;
}

std::size_t Wave::choose_pattern(std::size_t index, std::mt19937 &rng) const {
    double random_value =
        std::uniform_real_distribution<>(0, sum_weights[index])(rng);

    for (std::size_t i = 0; i < num_patterns; i++) {
        if (data[index][i])
            continue;
        if (random_value <= weights[i])
            return i;
        random_value -= weights[i];
    }

    return 0;
}

bool Wave::is_impossible() const {
    return std::any_of(remaining_patterns.begin(), remaining_patterns.end(),
                       [](std::size_t x) { return x == 0; });
}