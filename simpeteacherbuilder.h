#ifndef SIMPETEACHERBUILDER_H
#define SIMPETEACHERBUILDER_H

#include "teacherbuilder.h"

#include <QString>

class SimpleTeacherBuilder : public TeacherBuilder {
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

#endif // SIMPETEACHERBUILDER_H
