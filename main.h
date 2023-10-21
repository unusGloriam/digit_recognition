#ifndef MAIN_H
#define MAIN_H

#include <cstdint>
#include <tr1/array>

const auto LIMIT = 400;

const auto NUM_ROWS = 33;
const auto NUM_COLUMNS = 20;
const auto NUM_DIGITS = 10;

const auto POPULATION_SIZE = 20;
const auto CHROMOSOME_SIZE = (NUM_ROWS * NUM_COLUMNS);
const auto IS_MUTATION_PROBABILITY = true;

typedef std::tr1::array<std::tr1::array<uint8_t, 28>, 28>  Matrix;

#endif // MAIN_H