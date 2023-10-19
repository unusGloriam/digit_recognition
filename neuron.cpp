#include "neuron.h"

Neuron::Neuron() {
    sum_scaled_signals = 0;

    for (auto i = 0; i < NUM_ROWS; ++i) {
        for (auto j = 0; j < NUM_COLUMNS; ++j) {
            weight_matrix[i][j] = 0;
            scaled_matrix[i][j] = 0;
        }
    }
}

Matrix Neuron::get_weight_matrix() {
    return weight_matrix;
}

int Neuron::get_sum_scaled_signals() {
    return sum_scaled_signals;
}

int Neuron::count_sum_scaled_signals(Matrix input_matrix) {

    /* взвешиваем входные сигналы */
    for (int x = 0; x < NUM_ROWS; x++)  {
        for (int y = 0; y < NUM_COLUMNS; y++) {
            scaled_matrix[x][y] = input_matrix[x][y] * weight_matrix[x][y];
        }
    }

    sum_scaled_signals = 0;

    /* суммируем взвешенные сигналы */
    for (int x = 0; x < NUM_ROWS; x++) {
        for (int y = 0; y < NUM_COLUMNS; y++) {
            sum_scaled_signals += scaled_matrix[x][y];
        }
    }
    return sum_scaled_signals;
}

void Neuron::set_weight_matrix(Matrix w) {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLUMNS; ++j) {
            weight_matrix[i][j] = w[i][j];
        }
    }
}

void Neuron::dec_weight(Matrix input_matrix) {
    for (int x = 0; x < NUM_ROWS; x++) {
        for (int y = 0; y < NUM_COLUMNS; y++) {
            weight_matrix[x][y] -= input_matrix[x][y];
        }
    }
}

void Neuron::inc_weight(Matrix input_matrix) {
    for (int x = 0; x < NUM_ROWS; x++) {
        for (int y = 0; y < NUM_COLUMNS; y++) {
            weight_matrix[x][y] += input_matrix[x][y];
        }
    }
}

bool Neuron::recognition() {
    return (sum_scaled_signals >= LIMIT);
}
