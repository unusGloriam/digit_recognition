#ifndef NEURON_H
#define NEURON_H

#include "main.h"

class Neuron {
public:

    Neuron();

    ~Neuron() { }

    Matrix get_weight_matrix();

    int get_sum_scaled_signals();

    int count_sum_scaled_signals(Matrix in_matrix);

    void set_weight_matrix(Matrix w_matrix);

    void dec_weight(Matrix input);

    void inc_weight(Matrix input);

    bool recognition(/*Matrix input_matrix*/);

private:
    Matrix weight_matrix;
    Matrix scaled_matrix;
    int sum_scaled_signals;
};

#endif // NEURON_H
