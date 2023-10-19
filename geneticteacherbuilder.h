#ifndef GENETICTEACHERBUILDER_H
#define GENETICTEACHERBUILDER_H

#include "teacherbuilder.h"

class GeneticTeacherBuilder : public TeacherBuilder {
public:

    /**
     * @brief teach
     */

    void teach();

    /**
     * @brief set_directory
     * @param dir
     */

    void set_directory(QString dir);

    /**
     * @brief load_training_matrix
     */

    void load_training_matrix();
};

#endif // GENETICTEACHERBUILDER_H
