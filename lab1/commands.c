#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"

char getCommand() {
    printf("Please enter a command (enter h for help): ");
    char cmd;
    scanf(" %c", &cmd);
    return cmd;
}

void printHelp() {
    printf("a/1 to obtain all the students that got diploma\n");
    printf("b/2 to arrange subject A in ascending order\n");
    printf("c/3 to calculate the average and standard deviation\n");
    printf("d/4 to save all the above results in an output file\n");
    printf("e to exit\n");
}

void printStudent(struct Student s) {
    printf("%s\t\t%g\t\t%g\n", s.name, s.subjectA, s.subjectB);
}

void printDiplomaRecipients(struct Student students[MAX_STUDENTS]) {
    printf("All the students that diploma:\n");
    printf("STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].subjectA >= 50.0 && students[i].subjectB >= 50.0) {
            printStudent(students[i]);
        }
    }
}

void swapStudents(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Student students[], int low, int high) {
    float pivot = students[low].subjectA;
    int left = low;
    int right = high;

    while (left < right) {
        while (students[left].subjectA <= pivot) {
            left++;
        }
        while (students[right].subjectA > pivot) {
            right--;
        }

        if (left < right) {
            swapStudents(&students[left], &students[right]);
        }
    }

    swapStudents(&students[low], &students[right]);
    return right;
}

void quickSort(struct Student students[], int low, int high) {
    if (low < high) {
        int pIndex = partition(students, low, high);

        quickSort(students, low, pIndex - 1);
        quickSort(students, pIndex + 1, high);
    }
}

void arrangeA(struct Student students[MAX_STUDENTS]) {
    struct Student students_copy[MAX_STUDENTS];
    memcpy(students_copy, students, sizeof(struct Student) * MAX_STUDENTS);

    printf("Subject A in ascending order:\n");
    quickSort(students_copy, 0, MAX_STUDENTS - 1);

    printf("STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printStudent(students_copy[i]);
    }
}

void calcAvg(struct Student students[MAX_STUDENTS]) {
    printf("Average:\n");
    float sumSubjectA = 0;
    float sumSubjectB = 0;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        sumSubjectA += students[i].subjectA; 
        sumSubjectB += students[i].subjectB; 
    }

    printf(
        "SUBJECT A: %g\tSUBJECT B: %g\n\n",
        sumSubjectA / MAX_STUDENTS,
        sumSubjectB / MAX_STUDENTS
    );
}

void calcSigma(struct Student students[MAX_STUDENTS]) {
    printf("Standard deviation:\n");
    float sumSubjectA = 0.0;
    float sigSubjectA = 0.0;
    float avgSubjectA;

    float sumSubjectB = 0.0;
    float sigSubjectB = 0.0;
    float avgSubjectB;

    for (int i = 0; i < MAX_STUDENTS; i++) {
        sumSubjectA += students[i].subjectA;
        sumSubjectB += students[i].subjectB;
    }
    
    avgSubjectA = sumSubjectA / MAX_STUDENTS;
    avgSubjectB = sumSubjectB / MAX_STUDENTS;

    for (int i = 0; i < MAX_STUDENTS; i++) {
        sigSubjectA += pow(students[i].subjectA - avgSubjectA, 2);
        sigSubjectB += pow(students[i].subjectB - avgSubjectB, 2);
    }

    printf(
        "SUBJECT A: %g\tSUBJECT B: %g\n",
        sqrt(sigSubjectA / MAX_STUDENTS),
        sqrt(sigSubjectB / MAX_STUDENTS)
    );
}



void save(struct Student students[MAX_STUDENTS]) {
    char filename[] = "output.txt";
    printf("Writing to %s...\n", filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "All the students that diploma:\n");
    fprintf(file, "STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].subjectA >= 50.0 && students[i].subjectB >= 50.0) {
            fprintf(file, 
                "%s\t\t%g\t\t%g\n",
                students[i].name,
                students[i].subjectA,
                students[i].subjectB
            );
        }
    }

    struct Student students_copy[MAX_STUDENTS];
    memcpy(students_copy, students, sizeof(struct Student) * MAX_STUDENTS);

    fprintf(file, "\nSubject A in ascending order:\n");
    quickSort(students_copy, 0, MAX_STUDENTS - 1);

    fprintf(file, "STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        fprintf(file,  
            "%s\t\t%g\t\t%g\n",
            students[i].name,
            students[i].subjectA,
            students[i].subjectB
        );
    }

    fprintf(file, "\nAverage:\n");
    float sumSubjectA = 0;
    float sumSubjectB = 0;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        sumSubjectA += students[i].subjectA; 
        sumSubjectB += students[i].subjectB; 
    }

    fprintf(file, 
        "SUBJECT A: %g\tSUBJECT B: %g\n\n",
        sumSubjectA / MAX_STUDENTS,
        sumSubjectB / MAX_STUDENTS
    );

    fprintf(file, "Standard deviation:\n");
    sumSubjectA = 0.0;
    float sigSubjectA = 0.0;
    float avgSubjectA;

    sumSubjectB = 0.0;
    float sigSubjectB = 0.0;
    float avgSubjectB;

    for (int i = 0; i < MAX_STUDENTS; i++) {
        sumSubjectA += students[i].subjectA;
        sumSubjectB += students[i].subjectB;
    }
    
    avgSubjectA = sumSubjectA / MAX_STUDENTS;
    avgSubjectB = sumSubjectB / MAX_STUDENTS;

    for (int i = 0; i < MAX_STUDENTS; i++) {
        sigSubjectA += pow(students[i].subjectA - avgSubjectA, 2);
        sigSubjectB += pow(students[i].subjectB - avgSubjectB, 2);
    }

    fprintf(file, 
        "SUBJECT A: %g\tSUBJECT B: %g\n",
        sqrt(sigSubjectA / MAX_STUDENTS),
        sqrt(sigSubjectB / MAX_STUDENTS)
    );
}
