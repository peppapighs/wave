#include "generator.h"

Generator::Generator(
    std::size_t row, std::size_t col, const std::vector<double> &weights,
    const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
        &compatibility)
    : row(row), col(col), size(row * col), num_patterns(weights.size()),
      weights(weights), wave(row, col, weights),
      observer(row, col, compatibility) {}

Generator::Generator(
    int seed, std::size_t row, std::size_t col,
    const std::vector<double> &weights,
    const std::vector<std::array<std::vector<std::size_t>, NUM_DIRECTIONS>>
        &compatibility)
    : Generator(row, col, weights, compatibility) {
    rng.seed(seed);
}

Generator::ObserveStatus Generator::observe() {
    if (wave.is_impossible())
        return ObserveStatus::FAILED;

    long index = wave.get_min_entropy(rng);
    if (index == -1)
        return ObserveStatus::DONE;

    std::size_t pattern = wave.choose_pattern(index, rng);
    for (std::size_t i = 0; i < num_patterns; i++)
        if (wave.get_data(index, i) && i != pattern) {
            observer.remove_pattern(index, i);
            wave.remove_pattern(index, i);
        }

    return ObserveStatus::CONTINUE;
}

std::vector<std::size_t> Generator::generate() {
    while (true) {
        ObserveStatus status = observe();
        if (status == ObserveStatus::DONE)
            return wave.get_patterns();
        if (status == ObserveStatus::FAILED)
            return {};

        observer.propagate(wave);
    }
}