/*
 [x] - get user input
 [x] - execute a beep 
 [x] - execute a keystroke for the bell character
*/
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    // copy the current settings to the new settings
    newt = oldt;
    // disable canonical mode (line buffering) and echoing
    newt.c_lflag &= ~(ICANON | ECHO);
    int i;
    // set the new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c;
    
    while ((c = getchar()) != EOF) {
        printf("%c\n", c);
        if (c >= '0' && 0 <= '9') {
            for (i=0; i < c - '0'; i++) {
                printf("beep \a\r\n");
                fflush(stdout);
                sleep(1);
            }
        }
    }

    // reset terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
