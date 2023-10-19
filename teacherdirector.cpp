#include "teacherdirector.h"

void TeacherDirector::set_teacher(TeacherBuilder *pTeacherBuilder) {
    pTeacher = pTeacherBuilder;
}

void TeacherDirector::teach(QString dir) {
    pTeacher->create_new_teacher();
    pTeacher->set_directory(dir);
    pTeacher->load_training_matrix();
    pTeacher->teach();
}
