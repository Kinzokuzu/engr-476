#ifndef COMMANDS_H
#define COMMANDS_H

#include "readtable.h"

char getCommand();
void printHelp();
void printDiplomaRecipients(struct Student students[MAX_STUDENTS]);
void arrangeA(struct Student students[MAX_STUDENTS]);
void calcAvg(struct Student students[MAX_STUDENTS]);
void calcSigma(struct Student students[MAX_STUDENTS]);
void save(struct Student students[MAX_STUDENTS]);

#endif
