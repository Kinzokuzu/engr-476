#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readtable.h"

void readTable(
    char filename[BUFFER_LEN],
    char header[BUFFER_LEN],
    struct Student students[MAX_STUDENTS]
) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char buffer[BUFFER_LEN] = {'\0'};
    int row = 0;
    while ((fgets(buffer, BUFFER_LEN, file) != NULL) && row <= MAX_STUDENTS) {
        if (row == 0) {
            memcpy(header, buffer, BUFFER_LEN); 
        }
        else {
            char *token = strtok(buffer, "\t\n");

            struct Student s; 
            strncpy(s.name, token, NAME_LEN - 1);
            s.name[NAME_LEN - 1] = '\0';

            token = strtok(NULL, "\t\n");
            s.id = atoi(token);

            token = strtok(NULL, "\t\n");
            s.subjectA = atof(token);

            token = strtok(NULL, "\t\n");
            s.subjectB = atof(token);

            students[row - 1] = s;
        }

        row++;
    }

    fclose(file);
}

void printTable(char header[BUFFER_LEN], struct Student students[MAX_STUDENTS]) {
    printf("%s", header);
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printf(
            "%s\t\t%d\t\t%g\t\t%g\n",
            students[i].name,
            students[i].id,
            students[i].subjectA,
            students[i].subjectB
        );
    }
    printf("\n");
}
