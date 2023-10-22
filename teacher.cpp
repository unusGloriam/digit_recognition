#include "teacher.h"
#include "qdebug.h"

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
    /*for (int j = 0; j < training_matrix[0].size(); ++j) {
        for (int i = 0; i < 10; ++i) {
            if (training_matrix[i].size() > j){
                perceptron.set_input_matrix(training_matrix[i][j]);
                //int correct_index = perceptron.recognition();
                //if (correct_index != i) {
                    perceptron.teach(i);
                //}
            }
        }
//        if (j % 500 == 0 || j == 5922 || j == 5923){
//            qDebug() << "Passed j == " << j;
//        }
    }*/
    int max_size_index = 0;
    int max_size = training_matrix[0].size();
    for (int i = 1; i < NUM_DIGITS; ++i){
        int current_size = training_matrix[i].size();
        if (current_size > max_size){
            max_size = current_size;
            max_size_index = i;
        }
    }
    for (int k = 0; k < 100; ++k){
        for (int j = 0; j < training_matrix[max_size_index].size(); ++j) {
            for (int i = 0; i < 10; ++i) {
                if (j >= training_matrix[i].size()){
                    continue;
                }
                perceptron.set_input_matrix(training_matrix[i][j]);
                int correct_index = perceptron.recognition();
                if (correct_index != i) {
                    perceptron.teach(i);
                }
            }
        }
        if (k % 100 == 0){
            if (QFile::exists(QString(k))){ // файл с весами уже существует - удалим
                QFile::remove(QString(k));
            }
            QFile weights_file((QString(k)));
            if (weights_file.open(QIODevice::ReadWrite)){ // файл создался и открылся - пишем в него
                QTextStream stream(&weights_file);
                QVector<Matrix> weights_to_write = perceptron.get_weight_matrix();
                for (int i = 0; i < weights_to_write.size(); ++i){ // проходим по 10 (вроде как) векторам, соотв. цифрам 0-9, с их матрицами весов
                    for (size_t line = 0; line < weights_to_write[i].size(); ++line){ // проходим по строкам матрицы весов для очередной i цифры
                        for (size_t weight = 0; weight < weights_to_write[i][line].size(); ++weight){ // проходим по каждому весу в очередной строке очередной матрицы весов
                            stream << weights_to_write[i][line][weight] << " ";
                            stream.flush();
                        }
                        stream << Qt::endl;
                        stream.flush();
                    }
                }
                weights_file.close();
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
