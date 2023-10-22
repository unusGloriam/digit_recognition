#include "perceptron.h"
#include "qdebug.h"

Perceptron::Perceptron(Matrix in) {
    input_matrix = in;
}

Perceptron::Perceptron(Matrix in, QVector<Matrix> weights) {
    input_matrix = in;
    for (int i = 0; i < NUM_DIGITS; ++i) {
        neurons[i].set_weight_matrix(weights[i]);
    }
}

void Perceptron::set_input_matrix(Matrix in) {
    input_matrix = in;
}

void Perceptron::set_weight_matrix_at(Matrix weight, int i) {
    neurons[i].set_weight_matrix(weight);
}

void Perceptron::set_weight_matrix(QVector<Matrix> weights) {
    for (int i = 0; i < NUM_DIGITS; ++i) {
        neurons[i].set_weight_matrix(weights[i]);
    }
}

Matrix Perceptron::get_weight_matrix_at(int i) {
    return neurons[i].get_weight_matrix();
}

QVector<Matrix> Perceptron::get_weight_matrix() {
    QVector<Matrix> weight_matrix;
    for (int i = 0; i < NUM_DIGITS; ++i) {
        weight_matrix.push_back(neurons[i].get_weight_matrix());
    }
    return weight_matrix;
}

int Perceptron::get_sum_scaled_signals_at(int i) {
    return neurons[i].get_sum_scaled_signals();
}

QVector<int> Perceptron::get_sum_scaled_signals() {
    QVector<int> sum_scaled_signals;
    for (int i = 0; i < NUM_DIGITS; ++i) {
        sum_scaled_signals.push_back(neurons[i].get_sum_scaled_signals());
    }
    return sum_scaled_signals;
}

int Perceptron::recognition() {
    int index_neyron = 0;
    int max_sum_scaled_signals = neurons[index_neyron].count_sum_scaled_signals(input_matrix);
    //qDebug() << "0 sum: " << max_sum_scaled_signals;
    for (int i = 1; i < NUM_DIGITS; ++i) {
        int sum_scaled_signals = neurons[i].count_sum_scaled_signals(input_matrix);
        //qDebug() << i << " sum: " << sum_scaled_signals;
        if (sum_scaled_signals > max_sum_scaled_signals) {
            max_sum_scaled_signals = sum_scaled_signals;
            index_neyron = i;
        }
    }
//    for (int i = 0; i < NUM_DIGITS; ++i){
//        neurons[i].count_sum_scaled_signals(input_matrix);
//        if (neurons[i].recognition(input_matrix)){
//            index_neyron = i;
//            break;
//        }
//    }
    return index_neyron;
}

QVector<Matrix> Perceptron::teach(int correct_index) {
//    int max_sum_scaled_signals = neurons[0].count_sum_scaled_signals(input_matrix);
//    int max_counter = 1;
//    int max_index = 0;
    // сначала нейроны
    /*for (int i = 0; i < NUM_DIGITS; ++i){
        //neurons[i].count_sum_scaled_signals(input_matrix);
        if (neurons[i].recognition(input_matrix) && i != correct_index){
            neurons[i].dec_weight(input_matrix);
        } else if (i == correct_index && !neurons[i].recognition(input_matrix)){
            neurons[i].inc_weight(input_matrix);
        }
    }*/
    for (int i = 0; i < NUM_DIGITS; ++i) {
            if (i != correct_index && neurons[i].recognition()) {
                neurons[i].dec_weight(input_matrix);
            }
        }
        neurons[correct_index].inc_weight(input_matrix);
        return get_weight_matrix();

    // теперь максимумы
//    for (int i = 0; i < NUM_DIGITS; ++i){ // ищем наибольшую сумму
//        int current_sum = neurons[i].count_sum_scaled_signals(input_matrix);
//        if (current_sum > max_sum_scaled_signals){
//            max_sum_scaled_signals = current_sum;
//            max_counter = 1;
//            max_index = i;
//        } else if (current_sum == max_sum_scaled_signals){
//            ++max_counter;
//        }
//    }
//    if (max_counter > 1){ // если сразу несколько максимумов
//        for (int i = 0; i < NUM_DIGITS; ++i){
//            int current_sum = neurons[i].count_sum_scaled_signals(input_matrix);
//            if (i == correct_index){
//                neurons[correct_index].inc_weight(input_matrix);
//            } else if (current_sum == max_sum_scaled_signals){
//                neurons[i].dec_weight(input_matrix);
//            }
//        }
//    } else { // если один максимум...
//        if (max_index != correct_index){ // ...и он неправильный
//            neurons[max_index].dec_weight(input_matrix);
//            neurons[correct_index].inc_weight(input_matrix);
//        }
//    }

    return get_weight_matrix();
}
