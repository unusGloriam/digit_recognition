#ifndef TEACHERBUILDER_H
#define TEACHERBUILDER_H

#include "teacher.h"

class TeacherBuilder {
public:

    /**
     * @brief TeacherBuilder
     */

    TeacherBuilder();

    /**
     * @brief create_new_teacher
     */

    void create_new_teacher();

    /**
     * @brief teach
     */

    virtual void teach() = 0;

    /**
     * @brief load_training_matrix
     */

    virtual void load_training_matrix() = 0;

    /**
     * @brief set_directory
     * @param dir
     */

    virtual void set_directory(QString dir) = 0;

    /**
     * @brief get_teacher
     * @return
     */

    Teacher *get_teacher();

    /**
     * @brief get_weight_matrix
     * @return
     */

    QVector<Matrix> get_weight_matrix();

protected:
    Teacher *pTeacher;
};

#endif // TEACHERBUILDER_H
