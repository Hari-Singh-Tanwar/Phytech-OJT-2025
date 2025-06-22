#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    char reg_date[11]; // YYYY-MM-DD
} Student;

Student* load_students(int* count);
void save_students(Student* students, int count);
void register_student();
int generate_unique_id(Student* students, int count);

#endif