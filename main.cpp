#define _CRT_SECURE_NO_WARNINGS
#include <curses.h>
#include "Field.h"
#include "FieldControl.h"

void Display(FieldControl& field);

int main(void) {
	Tetrimino::InitMino();
	FieldControl field;
	initscr();
	start_color();

	noecho();
	cbreak();

	curs_set(0);
	keypad(stdscr, TRUE);

	timeout(0);

	int delay = 0;
	int waitCount = 2000;

	init_pair(1, COLOR_CYAN, COLOR_WHITE);
	init_pair(2, COLOR_YELLOW, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_WHITE);
	init_pair(4, COLOR_RED, COLOR_WHITE);
	init_pair(5, COLOR_BLUE, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(7, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);

	field.ChangeSize(20, 20);
	field.GenerateMino();

	while (1) {
		int ch;
		ch = getch();

		if (ch == 'Q') break;

		switch (ch) {
		case KEY_LEFT:
			field.MoveLeft();
			break;
		case KEY_RIGHT:
			field.MoveRight();
			break;
		case KEY_DOWN:
			field.FallAtOnce();
			break;
		case 'z':
			field.RotateMino(LEFT);
			break;
		case 'x':
			field.RotateMino(RIGHT);
			break;
		case ' ':
			field.ExchangeForHold();
			break;
		default:
			break;
		}


		if (delay%waitCount == 0) {
			field.MoveDown();
			if (field.LandingMino()) {
				field.VanishLine();
				field.GenerateMino();
				if (field.IsGameOver()) break;
			}
		}
		delay++;


		Display(field);
	}

	endwin();

	return 0;
}

void Display(FieldControl& field) {
	for (int y = 0; y < field.GetLine(); y++) {
		for (int x = 0; x < field.GetColumn(); x++) {
			switch (field.GetTrueValue(y, x)) {
			case 'C':
				attrset(COLOR_PAIR(1));
				mvaddch(y, x + 5, '#');
				break;
			case 'Y':
				attrset(COLOR_PAIR(2));
				mvaddch(y, x + 5, '#');
				break;
			case 'G':
				attrset(COLOR_PAIR(3));
				mvaddch(y, x + 5, '#');
				break;
			case 'R':
				attrset(COLOR_PAIR(4));
				mvaddch(y, x + 5, '#');
				break;
			case 'B':
				attrset(COLOR_PAIR(5));
				mvaddch(y, x + 5, '#');
				break;
			case 'W':
				attrset(COLOR_PAIR(6));
				mvaddch(y, x + 5, '#');
				break;
			case 'M':
				attrset(COLOR_PAIR(7));
				mvaddch(y, x + 5, '#');
				break;
			default:
				attrset(COLOR_PAIR(8));
				mvaddch(y, x + 5, '.');
				break;
			}
		}
	}
	Tetrimino mino = field.GetHold();
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			switch (mino(x, y))
			{
			case 'C':
				attrset(COLOR_PAIR(1));
				mvaddch(y + 1, x, '#');
				break;
			case 'Y':
				attrset(COLOR_PAIR(2));
				mvaddch(y + 1, x, '#');
				break;
			case 'G':
				attrset(COLOR_PAIR(3));
				mvaddch(y + 1, x, '#');
				break;
			case 'R':
				attrset(COLOR_PAIR(4));
				mvaddch(y + 1, x, '#');
				break;
			case 'B':
				attrset(COLOR_PAIR(5));
				mvaddch(y + 1, x, '#');
				break;
			case 'W':
				attrset(COLOR_PAIR(6));
				mvaddch(y + 1, x, '#');
				break;
			case 'M':
				attrset(COLOR_PAIR(7));
				mvaddch(y + 1, x, '#');
				break;
			default:
				attrset(COLOR_PAIR(8));
				mvaddch(y + 1, x, ' ');
				break;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		mino = field.CheckNext(i);
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				switch (mino(x, y))
				{
				case 'C':
					attrset(COLOR_PAIR(1));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				case 'Y':
					attrset(COLOR_PAIR(2));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				case 'G':
					attrset(COLOR_PAIR(3));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				case 'R':
					attrset(COLOR_PAIR(4));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				case 'B':
					attrset(COLOR_PAIR(5));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				case 'W':
					attrset(COLOR_PAIR(6));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				case 'M':
					attrset(COLOR_PAIR(7));
					mvaddch(y + 1 + i * 4, x + 26, '#');
					break;
				default:
					attrset(COLOR_PAIR(8));
					mvaddch(y + 1 + i * 4, x + 26, ' ');
					break;
				}
			}
		}
	}


	int count = 0;
	for (int y = 0; y < field.GetLine(); y++) {
		for (int x = 0; x < field.GetColumn(); x++) {
			if (field.GetTrueValue(y, x) == '#') count++;
		}
	}

	char msg[256];
	sprintf(msg, "Field: %d x %d, Puyo number: %03d", field.GetLine(), field.GetColumn(), count);
	mvaddstr(2, COLS - 35, msg);

	mvaddstr(0, 0, "hold");
	mvaddstr(0, 26, "next");

	refresh();
}