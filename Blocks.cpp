#include "Blocks.h"
// Cursor invisible 0, visible 1



// Cursor Position
void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Block constructor 
Block::Block(const int (*bkNum)[4][4][4]){
        this->shape.nth = bkNum;
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
void Block::up() {
    this->y--;
}
void Block::rotate() {
    this->rotationCount = (this->rotationCount + 1) % 4; // count stay within 0,1,2,3
}
void Block::setRotation(int rotation) {
	this->rotationCount = rotation;
}
void Block::setShape(Shape givenShape) {
    this->shape = givenShape;
}


void Backup::updateBackupBlock(Block* origin, Block& backupBlock)
{
    backupBlock.setX(origin->getX());
    backupBlock.setY(origin->getY());
    backupBlock.setRotation(origin->getRotationCount()); 
    backupBlock.setShape(origin->getShape());
}

void Backup::updateBackupTable(vector<vector<int>>& origin, vector<vector<int>>& backupTable)
{
    copy(origin.begin(), origin.end(), backupTable.begin());
}
