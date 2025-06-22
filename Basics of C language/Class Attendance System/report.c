#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"
#include "student.h"
#include "attendance.h"
#include "utils.h"

void generate_monthly_report() {
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

    char month[8]; // YYYY-MM
    printf("Enter month (YYYY-MM): ");
    fgets(month, sizeof(month), stdin);
    month[strcspn(month, "\n")] = 0;
    if (!is_valid_month(month)) {
        printf("Invalid month format.\n");
        free(students);
        free(attendance);
        return;
    }

    printf("\nMonthly Report for %s:\n", month);
    for (int i = 0; i < student_count; i++) {
        printf("\nStudent: %s (ID: %d)\n", students[i].name, students[i].id);
        printf("Date       | Status\n");
        printf("-----------|-------\n");

        for (int j = 0; j < att_count; j++) {
            if (strncmp(attendance[j].date, month, 7) == 0 && attendance[j].student_id == students[i].id) {
                if (compare_dates(students[i].reg_date, attendance[j].date) <= 0) {
                    printf("%s | %s\n", attendance[j].date, attendance[j].status);
                }
            }
        }
    }

    free(students);
    free(attendance);
}