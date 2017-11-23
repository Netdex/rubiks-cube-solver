#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "motor.h"

/* GPIO pinout for motors */
motor motors[] = {
    {9, 11, 12, 13, 14}, // F
    {8, 37, 38, 39, 40}, // B
    {8, 33, 34, 35, 36}, // L
    {8, 11, 12, 13, 14}, // R
    {8, 7, 8, 9, 10},    // F/B retract/extend
    {8, 15, 16, 17, 18}, // L/R retract/extend
};

union tick_state {
	struct {
		int f;
		int b;
		int l;
		int r;
		int fb;
		int lr;
	};
	int tick[6];
} tick = {{0,0,0,0,0,0}};

int main(void){
	iolib_init();
    for (int i = 0; i < 6; i++) {
        motor_init(motors[i]);
	}

	int ch;

	initscr();
	raw();	
	keypad(stdscr, TRUE);
	noecho();
	
	attron(A_BOLD);
	printw("rbs1d - debug");	
	attroff(A_BOLD);
	int d = 1;
	while(ch != 'q'){
		move(1,0);
		printw("F:\t%d\nB:\t%d\nL:\t%d\nR:\t%d\nFB:\t%d\nLR:\t%d\n",
				tick.f, tick.b, tick.l, tick.r, tick.fb, tick.lr);
		refresh();

		ch = getch();
		switch(ch){
		case KEY_UP:
			tick.f += d; 
			step(tick.f, motors[0]);
			break;
		case KEY_DOWN:
			tick.b += d;
			step(tick.b, motors[1]);
			break;
		case KEY_LEFT:
			tick.l += d;
			step(tick.l, motors[2]);
			break;
		case KEY_RIGHT:
			tick.r += d;
			step(tick.r, motors[3]);
			break;
		case '[':
			tick.fb += d;
			step(tick.fb, motors[4]);
			break;
		case ']':
			tick.lr += d;
			step(tick.lr, motors[5]);
			break;
		case '=':
			d = 1;
			break;
		case '-':
			d = -1;
			break;
		}
	}
	endwin();	

	return 0;
}
