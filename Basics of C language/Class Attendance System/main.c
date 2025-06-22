#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "attendance.h"
#include "report.h"

void display_menu() {
    printf("\nClass Attendance System\n");
    printf("1. Register New Student\n");
    printf("2. Take Attendance\n");
    printf("3. View Past Attendance\n");
    printf("4. Generate Monthly Report\n");
    printf("5. Exit\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear newline

        switch (choice) {
            case 1:
                register_student();
                break;
            case 2:
                take_attendance();
                break;
            case 3:
                view_past_attendance();
                break;
            case 4:
                generate_monthly_report();
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
