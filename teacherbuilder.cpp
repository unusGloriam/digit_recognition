#include "teacherbuilder.h"

TeacherBuilder::TeacherBuilder() {

}

void TeacherBuilder::create_new_teacher() {
    pTeacher = new Teacher();
}

Teacher* TeacherBuilder::get_teacher() {
    return pTeacher;
}

QVector<Matrix> TeacherBuilder::get_weight_matrix() {
    return pTeacher->get_weight_matrix();
}
