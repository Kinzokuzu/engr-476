#include <stdio.h>

#include "commands.h"
#include "readtable.h"

int main() {
    printf("Please enter input file name: ");
    char fileName[BUFFER_LEN];
    scanf("%s", fileName);

    char header[BUFFER_LEN];
    struct Student students[MAX_STUDENTS];
    readTable(fileName, header, students);
    printf("%s:\n\n", fileName);
    printTable(header, students);

    // Execute command
    char cmd;
    while ((cmd = getCommand()) != 'e') {
        switch (cmd) {  
            case 'h':
                printHelp();
                break;
            case 'a':
            case '1':
                printDiplomaRecipients(students);
                break;
            case 'b':
            case '2':
                arrangeA(students);
                break;
            case 'c':
            case '3':
                calcAvg(students);
                calcSigma(students);
                break;
            case 'd':
            case '4':
                save(students);
                break;
        }
    
        printf("\n");
    }

    return 0;
}
