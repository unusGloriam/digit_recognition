#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "main.h"
#include "neuron.h"

#include <QVector>

class Perceptron {
public:

    /**
     * @brief Конструктор по умолчанию
     */

    Perceptron() {}

    /**
     * @brief Конструктор инициализации
     * @param i_matrix
     */

    Perceptron(Matrix i_matrix);

    /**
     * @brief Конструктор инициализации
     * @param i_matrix
     * @param w_vmatrix
     */

    Perceptron(Matrix i_matrix, QVector<Matrix> w_vmatrix);

    /**
     * @brief Деструктор
    */

    ~Perceptron() {}

    /**
     * @brief Метод установки матрицы входных весов
     * @param in_matirx
     */

    void set_input_matrix(Matrix in_matirx);

    /**
     * @brief Метод установки матрицы входных сигналов для нейрона с индексом
     * @param w_matrix
     * @param index_symbol
     */

    void set_weight_matrix_at(Matrix w_matrix, int index_symbol);

    /**
     * @brief Метод установки матрицы весов
     * @param w_vmatrix
     */

    void set_weight_matrix(QVector<Matrix> w_vmatrix);

    /**
     * @brief Метод получения матрицы весов для нейрона по его индексу
     * @param index_symbol Индекс нейрона
     * @return
     */

    Matrix get_weight_matrix_at(int index_symbol);

    /**
     * @brief Метод получения матрицы весов
     * @return
     */

    QVector<Matrix> get_weight_matrix();

    /**
     * @brief Метод получения взвешенной суммы входных сигналов одного нейрона
     * @param index_symbol
     * @return
     */

    int get_sum_scaled_signals_at(int index_symbol);

    /**
     * @brief Метод получения взвешенных сумм входных сигналов всех нейронов
     * @return
     */

    QVector<int> get_sum_scaled_signals();

    /**
     * @brief Метод распознавания символа. Возвращает индекс распознанного символа
     * @return
     */

    int recognition();

    /**
     * @brief Изменение весов синапсов у нейронов в зависимости от параметра
     * @param correct_index_symbol
     * @return
     */

    QVector<Matrix> teach(int correct_index_symbol);

protected:
    Neuron neurons[NUM_DIGITS]; //! @brief массив нейронов
    Matrix input_matrix; //! @brief матрица входных сигналов
};
#endif // PERCEPTRON_H
