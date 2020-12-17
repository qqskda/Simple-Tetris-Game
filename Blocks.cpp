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
Block::Block(int rotation, int bkNum){
    shape.rotation = rotation;
    shape.nth = bkNum;
    }

void Block::down() { // block move down
    this->y++;
}
void Block::left() {
    this->x--;
}
void Block::right() {
    this->x++;
}
void Block::rotate() {
    this->rotationCount = (this->rotationCount + 1) % 4; // count stay within 0,1,2,3
}
void Block::setRotation(int rotation) {
	this->rotationCount = rotation;
}
void Block::setShape(int(&arr)[4][4][4]) {
    this->shape = arr;
}

void Backup::updateBackupBlock(Block* origin, Block& backupBlock)
{
    backupBlock.setX(origin->getX());
    backupBlock.setY(origin->getY());
    backupBlock.setRotation(origin->getRotationCount()); // save the original one
    backupBlock.setShape(origin->getShape());
}

void Backup::updateBackupTable(vector<vector<int>>& origin, vector<vector<int>>& backupTable)
{
    backupTable.resize(origin.size(), vector<int>(origin.size()));
    copy(origin.begin(), origin.end(), backupTable.begin());
}

void Backup::restoreOriginTable(vector<vector<int>>& origin, vector<vector<int>>& backupTable)
{
    copy(backupTable.begin(), backupTable.end(), origin.begin());
}
