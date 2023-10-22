#ifndef NEURON_H
#define NEURON_H

#include "main.h"

class Neuron {
public:

    /**
     * @brief Neuron constructor
     */

    Neuron();

    /**
     * @brief Neuron destructor
    */

    ~Neuron() { }

    /**
     * @brief get_weight_matrix
     * @return
     */

    Matrix get_weight_matrix();

    /**
     * @brief get_sum_scaled_signals
     * @return
     */

    int get_sum_scaled_signals();

    /**
     * @brief count_sum_scaled_signals
     * @param in_matrix
     * @return
     */

    int count_sum_scaled_signals(Matrix in_matrix);

    /**
     * @brief set_weight_matrix
     * @param w_matrix
     */

    void set_weight_matrix(Matrix w_matrix);

    /**
     * @brief dec_weight
     * @param input
     * @details Метод уменьшения весов синапсов
     */

    void dec_weight(Matrix input);

    /**
     * @brief inc_weight
     * @param input
     * @details Метод уменьшения весов
     */

    void inc_weight(Matrix input);

    /**
     * @brief recognition
     * @return
     */

    bool recognition(Matrix input_matrix);

private:
    Matrix weight_matrix; //! @brief веса синопсов
    Matrix scaled_matrix; //! @brief масштабированные входные сигналы
    int sum_scaled_signals; //! @brief взвешенная сумма входных сигналов
};

#endif // NEURON_H
