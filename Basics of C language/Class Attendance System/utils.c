#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void get_current_date(char* date) {
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    strftime(date, 11, "%Y-%m-%d", tm);
}

int compare_dates(const char* date1, const char* date2) {
    // Simple string comparison since YYYY-MM-DD sorts lexicographically
    return strcmp(date1, date2);
}

int is_valid_date(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return 0;
    }
    int year, month, day;
    sscanf(date, "%d-%d-%d", &year, &month, &day);
    if (month < 1 || month > 12 || day < 1 || day > 31) return 0;
    return 1;
}

int is_valid_month(const char* month) {
    if (strlen(month) != 7) return 0;
    if (month[4] != '-') return 0;
    for (int i = 0; i < 7; i++) {
        if (i == 4) continue;
        if (month[i] < '0' || month[i] > '9') return 0;
    }
    int year, m;
    sscanf(month, "%d-%d", &year, &m);
    if (m < 1 || m > 12) return 0;
    return 1;
}