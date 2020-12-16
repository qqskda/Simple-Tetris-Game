#include "Blocks.h"

// Cursor invisible 0, visible 1
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// Cursor Position
void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Block parent class
Block::Block(const int(&arr)[4][4][4]) : shape(arr) {}

void Block::down() { // block move down
    this->y ++;
}
void Block::left() {
    this->x --;
}
void Block::right() {
    this->x++;
}
void Block::rotate() {
    this->rotationCount = (this->rotationCount + 1) % 4; // count stay within 0,1,2,3
}
