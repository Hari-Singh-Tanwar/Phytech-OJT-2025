#ifndef ATTENDANCE_H
#define ATTENDANCE_H

typedef struct {
    char date[11]; // YYYY-MM-DD
    int student_id;
    char status[10]; // present, absent, N/A
} Attendance;

Attendance* load_attendance(int* count);
void save_attendance(Attendance* attendance, int count);
void take_attendance();
void view_past_attendance();

#endif