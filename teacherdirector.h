#ifndef TEACHERDIRECTOR_H
#define TEACHERDIRECTOR_H

#include "teacherbuilder.h"

class TeacherDirector {
public:

    /**
     * @brief set_teacher
     * @param tb
     */

    void set_teacher(TeacherBuilder *tb);

    void teach(QString dir);

private:
    TeacherBuilder *pTeacher;
};

#endif // TEACHERDIRECTOR_H
