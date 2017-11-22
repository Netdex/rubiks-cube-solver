#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "motor.h"

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
			break;
		case KEY_DOWN:
			tick.b += d;
			break;
		case KEY_LEFT:
			tick.l += d;
			break;
		case KEY_RIGHT:
			tick.r += d;
			break;
		case '[':
			tick.fb += d;
			break;
		case ']':
			tick.lr += d;
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
