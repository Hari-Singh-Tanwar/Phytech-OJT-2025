cmake_minimum_required(VERSION 3.10)

project(AttendanceSystem C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    main.c
    student.c
    attendance.c
    report.c
    utils.c
)

set(HEADERS
    student.h
    attendance.h
    report.h
    utils.h
)

add_executable(attendance ${SOURCES} ${HEADERS})

target_include_directories(attendance PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})