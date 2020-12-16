
#include "Table.h"


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
    Block bkBlock(block1);
    vector<vector<int>> bkTable;
    Backup::updateBackupBlock(this->blockObject, bkBlock); // backup the original block
    Backup::updateBackupTable(this->table, bkTable);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int Y = j + this->blockObject->Block::getY();
            int X = i + this->blockObject->Block::getX();
            int blockValue = this->blockObject->Block::getShape(this->blockObject->Block::getRotationCount(), i, j);
            switch (key)
            {
            case 1: // creation of the block
                this->table[Y][X] = blockValue;
                break;
            case 2: // Remove the block from the table
                if (this->table[Y][X] == 2) this->table[Y][X] = 0;
                break;
            case 3: // move
                if (blockValue != 2) continue; // if it is not block (empty) -> all good
                if (this->table[Y][X] == 0) // when it is empty space
                {
                    this->table[Y][X] = blockValue; // move the block to the empty space
                }
                else if (table[Y][X] == 2) 
                {
                    Backup::restoreOriginTable(this->table, bkTable);
                    this->blockObject->setX(bkBlock.getX());
                    this->blockObject->setY(bkBlock.getY());
                    return; // stop the changings
                }
                break;
            case 4: // rotate of the block from the current position 
                if (blockValue != 2) continue; // if it is not block (empty) -> all good
                if (this->table[Y][X] == 0) // when it is empty space
                {
                    this->table[Y][X] = blockValue; // move the block to the empty space
                } 
                else if (table[Y][X] == 1)
                {
                    Backup::restoreOriginTable(this->table, bkTable);
                    this->blockObject->setRotation(bkBlock.getRotationCount() + 3 % 4);
                    return; // stop the changings
                }
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
    blockUpdate((int) 1); // update the block on the table
}

void GameTable::moveBlock(int inputKey)
{
    blockUpdate((int)2);  // remove the block

    // Updating the block location along with the inputKey
    if (inputKey == DOWN) this->blockObject->down();
    else if (inputKey == LEFT) this->blockObject->left();
    else if (inputKey == RIGHT) this->blockObject->right();

    // Now update the table with the new block location
    blockUpdate((int)3);
}

void GameTable::rotateBlock()
{
    blockUpdate((int)2); // remove the block from the table
    this->blockObject->rotate(); // rotate the block
    blockUpdate((int)4); // update the block if it is empty place
}
