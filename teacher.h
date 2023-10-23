#ifndef TEACHER_H
#define TEACHER_H

#include "perceptron.h"
#include <QFileDialog>

class Teacher {
public:

    Teacher() {}

    Teacher(QVector< QVector<Matrix> >);

    ~Teacher() {}

    void set_weight_matrix(QVector<Matrix> w_matrix);

    void set_training_matrix(QVector< QVector<Matrix> >);

    QVector<Matrix> get_weight_matrix();

    QString get_directory();

    Perceptron get_perceptron();

    QVector< QVector<Matrix> > get_training_matrix();

    void teach();

    void load_training_matrix() {}

    void set_directory(QString d);

private:

    Perceptron perceptron;
    QVector< QVector<Matrix> > training_matrix;
};


#endif // TEACHER_H
