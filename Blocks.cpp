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
        y++;
    }
    void Block::left() {
        x--;
    }
    void Block::right() {
        x++;
    }
    void Block::rotate() {
        rotationCount = (rotationCount + 1) % 4; // count stay within 0,1,2,3
    }

class Block1 : public Block {
public:
    Block1() : Block::Block(block1) {}
};

class Block2 : public Block {
public:
    Block2() : Block(block2) {}
};
class Block3 : public Block {
public:
    Block3() : Block(block3) {}
};
class Block4 : public Block {
public:
    Block4() : Block(block4) {}
};
class Block5 : public Block {
public:
    Block5() : Block(block5) {}
};

