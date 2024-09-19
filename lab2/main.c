#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define FLAG_LEN 8

struct termios orig_termios; // original terminal attributes

void disableRawInput() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawInput() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawInput);

    struct termios raw = orig_termios;
    raw.c_iflag &= ~( ICRNL| IXON);                  // c_iflag: input flags
    raw.c_oflag &= ~(OPOST);                         // c_oflag: ouput flags
    raw.c_lflag &= ~(/*ECHO |*/ ICANON | IEXTEN | ISIG); // c_lflag: local flags
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int setFlagBuffer(char ch, char buffer[FLAG_LEN+1], int idx) {
    if (idx < FLAG_LEN) {
        buffer[idx] = ch;
        idx++;
    }
    else {
        for (int i = 0; i < FLAG_LEN-1; i++) {
            buffer[i] = buffer[i+1];
        }
        buffer[FLAG_LEN-1] = ch;
    }

    return idx;
}

bool isFrameFlag(char buffer[FLAG_LEN+1]) {
    return !strcmp(buffer, "01111110");
}

int main() {
    enableRawInput();

    char flag_buff[FLAG_LEN+1] = {'\0'};
    int idx = 0;
    char ch;
    while (read(STDIN_FILENO, &ch, 1) == 1 /*&& ch != 'e'*/) {
        if (ch == 'e') break;

        idx = setFlagBuffer(ch, flag_buff, idx);
        if (isFrameFlag(flag_buff)) {
            // Do something
        }

        if (iscntrl(ch)) { // is control character
            printf("%d\r", ch);
        }
        else {
            printf("%c\r", ch);
        }
    }

    return 0;
}
