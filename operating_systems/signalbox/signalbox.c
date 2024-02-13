/*
 * TODO
 *    [x] - Print a box 
 *    [x] - Get terminal size in L and W - use SIGWINCH signal to get a window size change
 *    [x] - determine size of the terminal - use ioctl and TIOCGWINSZ      
 * */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

volatile sig_atomic_t resized = 0;
void draw_box() {
        // get height and width of terminal 
	struct winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	int width = ws.ws_col;
	int height = ws.ws_row;

	// print top row
	for (int i = 0; i < height / 3; i++) {
		printf("\n");
	}	
	for (int i = 0; i < width / 3; i++) {
		printf(" ");
	}
	for (int i = 0; i < width / 3; i++) {
		printf("-");
	}
	printf("\n");

	// print middle rows of box
	for (int i = 0; i < height / 3; i++) {
		// left column
		for (int i = 0; i < width / 3; i++) {
			printf(" ");
		}
		printf("|");
		for (int j = 0; j < (width / 3) - 2; j++) {
			printf(" ");
		}
		// right column
		printf("|\n");
	}
	// Print the bottom row of the box
	for (int i = 0; i < width / 3; i++) {
		printf(" ");
	}
	for (int i = 0; i < width / 3; i++) {
		printf("-");
	}
	for (int i = 0; i < height / 3; i++) {
		printf("\n");
	}		
}

void handle(int sig) {
	if (sig == SIGWINCH) {
		resized = 1;
	} 
}


int main () {
	printf("Starting signalbox program\n");
	signal(SIGWINCH, handle);
	draw_box();
	while(1) {
		if (resized) {
			draw_box();
			resized = 0;
		}
	};
	return 0;
}
