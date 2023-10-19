#include "teacher.h"

Teacher::Teacher( QVector< QVector<Matrix> > t_matrix) {
    training_matrix = t_matrix;
}

void Teacher::set_weight_matrix(QVector<Matrix> w_matrix) {
    perceptron.set_weight_matrix(w_matrix);
}

void Teacher::set_training_matrix( QVector< QVector<Matrix> > t_matrix) {
    training_matrix = t_matrix;
}

QVector<Matrix> Teacher::get_weight_matrix() {
    return perceptron.get_weight_matrix();
}

QVector< QVector<Matrix> > Teacher::get_training_matrix() {
    return training_matrix;
}

void Teacher::teach() {
    for (int j = 0; j < training_matrix[0].size(); ++j) {
        for (int i = 0; i < 10; ++i) {
            perceptron.set_input_matrix(training_matrix[i][j]);
            int correct_index = perceptron.recognition();
            if (correct_index != i) {
                perceptron.teach(i);
            }
        }
    }
}

QString Teacher::get_directory() {
    return dir;
}

Perceptron Teacher::get_perceptron() {
    return perceptron;
}

void Teacher::set_directory(QString d) {
    dir = d;
}
