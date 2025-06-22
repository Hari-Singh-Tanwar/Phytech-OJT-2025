#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"
#include "attendance.h"
#include "utils.h"

Student* load_students(int* count) {
    FILE* file = fopen("students.csv", "r");
    if (!file) {
        *count = 0;
        return NULL;
    }

    Student* students = NULL;
    *count = 0;
    char line[256];
    fgets(line, sizeof(line), file); // Skip header
    while (fgets(line, sizeof(line), file)) {
        students = realloc(students, (*count + 1) * sizeof(Student));
        sscanf(line, "%d,%49[^,],%10s", &students[*count].id, students[*count].name, students[*count].reg_date);
        (*count)++;
    }
    fclose(file);
    return students;
}

void save_students(Student* students, int count) {
    // Sort students by name
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    FILE* file = fopen("students.csv", "w");
    if (!file) {
        printf("Error opening students.csv for writing.\n");
        return;
    }
    fprintf(file, "ID,Name,RegistrationDate\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s\n", students[i].id, students[i].name, students[i].reg_date);
    }
    fclose(file);
}

int generate_unique_id(Student* students, int count) {
    int max_id = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id > max_id) max_id = students[i].id;
    }
    return max_id + 1;
}

void register_student() {
    int student_count;
    Student* students = load_students(&student_count);
    Student new_student;

    printf("Enter student name: ");
    fgets(new_student.name, MAX_NAME, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0; // Remove newline
    if (strlen(new_student.name) == 0) {
        printf("Name cannot be empty.\n");
        free(students);
        return;
    }

    new_student.id = generate_unique_id(students, student_count);
    get_current_date(new_student.reg_date);

    students = realloc(students, (student_count + 1) * sizeof(Student));
    students[student_count] = new_student;
    student_count++;

    save_students(students, student_count);

    // Update attendance.csv with N/A for past dates
    int att_count;
    Attendance* att_records = load_attendance(&att_count);
    if (att_records) {
        FILE* file = fopen("attendance.csv", "a");
        if (file) {
            for (int i = 0; i < att_count; i++) {
                if (compare_dates(att_records[i].date, new_student.reg_date) < 0) {
                    fprintf(file, "%s,%d,N/A\n", att_records[i].date, new_student.id);
                }
            }
            fclose(file);
        }
        free(att_records);
    }

    printf("Student %s registered with ID %d.\n", new_student.name, new_student.id);
    free(students);
}