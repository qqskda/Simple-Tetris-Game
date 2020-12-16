#include <vector>
#include <iostream>
#include "Table.h"
#include <ctime>



using namespace std;

void GameTable::GameTableDraw()
{
    for (int row = 0; row < this->yAxis; ++row)
    {
        for (int col = 0; col < this->xAxis; ++col)
        {
            if (this->table[row][col] == 1) cout << "* ";
            else if (this->table[row][col] == 2) cout << "X ";
            else cout << "  ";
        }
        cout << "\n";
    }
}

void GameTable::blockUpdate(int key)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int Y = j + this->blockObject->Block::getY();
            int X = i + this->blockObject->Block::getX();
            switch (key)
            {
            case 0: // updating the block
                if (this->table[Y][X] == 0)
                this->table[Y][X] = this->blockObject->Block::getShape(this->blockObject->Block::getRotationCount(), i, j);
                break;
            case 1: // creation of the block
                this->table[Y][X] = this->blockObject->Block::getShape(this->blockObject->Block::getRotationCount(), i, j);
                break;
            case 2: // Remove the block from the table
                if (this->table[Y][X] == 2) this->table[Y][X] = 0;
                break;
            }
           
        }
    }
}

void GameTable::createBlock()
{
    srand((unsigned int)time(NULL));
    int blockSelection = rand() % 5 + 1; // 1-5
    switch (blockSelection)
    {
    case 1:
        this->blockObject = new Block1;
        break;
    case 2:
        this->blockObject = new Block2;
        break;
    case 3:
        this->blockObject = new Block3;
        break;
    case 4:
        this->blockObject = new Block4;
        break;
    default:
        this->blockObject = new Block5;
    }
    blockUpdate((int) 1);
}

void GameTable::moveBlock(int inputKey)
{
    blockUpdate((int)2);  // remove the block

    // Updating the block location along with the inputKey
    if (inputKey == DOWN) this->blockObject->down();
    else if (inputKey == LEFT) this->blockObject->left();
    else if (inputKey == RIGHT) this->blockObject->right();

    // Now update the table with the new block location
    blockUpdate((int)0);
}

void GameTable::rotateBlock()
{
    this->blockObject->Block::rotate(); // rotate the block
    blockUpdate((int)2); // remove the block from the table
    blockUpdate((int)0); // update the block if it is empty place
}
