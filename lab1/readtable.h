#ifndef READTABLE_H
#define READTABLE_H

#define MAX_STUDENTS 7
#define BUFFER_LEN 64
#define NAME_LEN 16

struct Student {
    char name[NAME_LEN];
    int id;
    float subjectA;
    float subjectB;
};

void readTable(
    char filename[BUFFER_LEN],
    char header[BUFFER_LEN],
    struct Student students[MAX_STUDENTS]
);

void printTable(char header[BUFFER_LEN], struct Student students[MAX_STUDENTS]);

#endif
