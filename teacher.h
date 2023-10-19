#ifndef TEACHER_H
#define TEACHER_H

#include "perceptron.h"

/**
 * @brief Содержит алгоритмы обучения нейронной сети
 * @details Обучает персептрон для получения весов синапсов для конкретной выборки данных
 */

class Teacher {
public:

    /**
     * @brief Teacher
     */

    Teacher() {}

    /**
     * @brief
     */

    Teacher(QVector< QVector<Matrix> >);

    /**
     * @brief
     */

    ~Teacher() {}

    /**
     * @brief set_weight_matrix
     * @param w_matrix
     */

    void set_weight_matrix(QVector<Matrix> w_matrix);

    /**
     * @brief set_training_matrix
     */

    void set_training_matrix(QVector< QVector<Matrix> >);

    /**
     * @brief get_weight_matrix
     * @return
     */

    QVector<Matrix> get_weight_matrix();

    /**
     * @brief get_directory
     * @return
     */

    QString get_directory();

    /**
     * @brief get_perceptron
     * @return
     */

    Perceptron get_perceptron();

    /**
     * @brief get_training_matrix
     * @return
     */

    QVector< QVector<Matrix> > get_training_matrix();

    /**
     * @brief teach
     */

    void teach();

    /**
     * @brief load_training_matrix
     */

    void load_training_matrix() {}

    /**
     * @brief set_directory
     * @param d
     */

    void set_directory(QString d);

private:

    Perceptron perceptron; //! @brief
    QVector< QVector<Matrix> > training_matrix; //! @brief
    QString dir; //! @brief
};


#endif // TEACHER_H
