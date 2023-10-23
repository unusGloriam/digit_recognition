#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "main.h"
#include "neuron.h"

#include <QVector>

class Perceptron {
public:

    Perceptron() {}

    Perceptron(Matrix i_matrix);

    Perceptron(Matrix i_matrix, QVector<Matrix> w_vmatrix);

    ~Perceptron() {}

    void set_input_matrix(Matrix in_matirx);

    void set_weight_matrix_at(Matrix w_matrix, int index_symbol);

    void set_weight_matrix(QVector<Matrix> w_vmatrix);

    Matrix get_weight_matrix_at(int index_symbol);

    QVector<Matrix> get_weight_matrix();

    int get_sum_scaled_signals_at(int index_symbol);

    QVector<int> get_sum_scaled_signals();

    int recognition();

    QVector<Matrix> teach(int correct_index_symbol);

protected:
    Neuron neurons[NUM_DIGITS];
    Matrix input_matrix;
};
#endif // PERCEPTRON_H
