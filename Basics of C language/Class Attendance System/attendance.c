#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attendance.h"
#include "student.h"
#include "utils.h"

Attendance* load_attendance(int* count) {
    FILE* file = fopen("attendance.csv", "r");
    if (!file) {
        *count = 0;
        return NULL;
    }

    Attendance* attendance = NULL;
    *count = 0;
    char line[256];
    fgets(line, sizeof(line), file); // Skip header
    while (fgets(line, sizeof(line), file)) {
        attendance = realloc(attendance, (*count + 1) * sizeof(Attendance));
        sscanf(line, "%10[^,],%d,%9s", attendance[*count].date, &attendance[*count].student_id, attendance[*count].status);
        (*count)++;
    }
    fclose(file);
    return attendance;
}

void save_attendance(Attendance* attendance, int count) {
    FILE* file = fopen("attendance.csv", "w");
    if (!file) {
        printf("Error opening attendance.csv for writing.\n");
        return;
    }
    fprintf(file, "Date,StudentID,Status\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%s\n", attendance[i].date, attendance[i].student_id, attendance[i].status);
    }
    fclose(file);
}

void take_attendance() {
    int student_count;
    Student* students = load_students(&student_count);
    if (student_count == 0) {
        printf("No students registered.\n");
        free(students);
        return;
    }

    char date[11];
    printf("Enter date (YYYY-MM-DD, press Enter for today): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;
    if (strlen(date) == 0) {
        get_current_date(date);
    }
    if (!is_valid_date(date)) {
        printf("Invalid date format.\n");
        free(students);
        return;
    }

    int att_count;
    Attendance* attendance = load_attendance(&att_count);

    printf("Taking attendance for %s:\n", date);
    for (int i = 0; i < student_count; i++) {
        if (compare_dates(students[i].reg_date, date) <= 0) {
            printf("Student: %s (ID: %d) - Enter status (p for present, a for absent): ", students[i].name, students[i].id);
            char status;
            scanf(" %c", &status);
            while (getchar() != '\n'); // Clear input buffer
            if (status != 'p' && status != 'a') {
                printf("Invalid status, skipping.\n");
                continue;
            }

            attendance = realloc(attendance, (att_count + 1) * sizeof(Attendance));
            strcpy(attendance[att_count].date, date);
            attendance[att_count].student_id = students[i].id;
            strcpy(attendance[att_count].status, status == 'p' ? "present" : "absent");
            att_count++;
        }
    }

    save_attendance(attendance, att_count);
    printf("Attendance recorded.\n");

    free(students);
    free(attendance);
}

void view_past_attendance() {
    int student_count;
    Student* students = load_students(&student_count);
    int att_count;
    Attendance* attendance = load_attendance(&att_count);

    if (att_count == 0) {
        printf("No attendance records found.\n");
        free(students);
        free(attendance);
        return;
    }

    char date[11];
    printf("Enter date to view (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;
    if (!is_valid_date(date)) {
        printf("Invalid date format.\n");
        free(students);
        free(attendance);
        return;
    }

    printf("\nAttendance for %s:\n", date);
    for (int i = 0; i < student_count; i++) {
        if (compare_dates(students[i].reg_date, date) <= 0) {
            int found = 0;
            for (int j = 0; j < att_count; j++) {
                if (strcmp(attendance[j].date, date) == 0 && attendance[j].student_id == students[i].id) {
                    printf("%s (ID: %d): %s\n", students[i].name, students[i].id, attendance[j].status);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("%s (ID: %d): No record\n", students[i].name, students[i].id);
        }
    }

    free(students);
    free(attendance);
}