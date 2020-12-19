#include "Table.h"


using namespace std;

void GameTable::GameTableDraw()
{
    for (int row = 0; row < this->yAxis; ++row)
    {
        for (int col = 0; col < this->xAxis; ++col)
        {
            if (this->table[row][col] == enumBlock::WALL || this->table[row][col] == enumBlock::BOTTOM) cout << (char)178u << " ";
            else if (this->table[row][col] == enumBlock::BLK || this->table[row][col] == enumBlock::FBLK) cout << (char)254u << " ";
            else cout << "  ";
        }
        cout << "\n";
    }
}

int GameTable::blockUpdate(int key)
{
    // the shape will be accessed 4*4 times -> better copy it in the given size.
    // Will the access consumes more expensive than copying the entire shape?
    auto blockShape = *this->blockObject->getShape().nth;
    int rotation = this->blockObject->getRotationCount();
    int i, j, Y, X, blockValue, thisTableVal;
    int currentY = this->blockObject->getY(), currentX = this->blockObject->getX();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            Y = j + currentY;
            X = i + currentX;
            blockValue = blockShape[rotation][i][j];
            if (blockValue == 2)  thisTableVal = this->table[Y][X];


            switch (key)
            {
            case 0: // creation of the block
                this->table[Y][X] = blockValue;
                break;
            case 1: // Remove the block from the table
                if (blockValue == 2 && thisTableVal == enumBlock::BLK) {
                    this->table[Y][X] = enumBlock::SPACE;
                }
                break;
            case 2: // move
                if (blockValue == enumBlock::BLK)
                {
                    if (thisTableVal == enumBlock::SPACE)
                    {
                        this->table[Y][X] = blockValue; // move the block to the empty space
                    }
                    else if (thisTableVal == enumBlock::WALL)
                    {
                        return 1; // stop the changings
                    }
                    else if (thisTableVal != enumBlock::BLK) // Not Space, not Wall, Not BLK ->  FBLK, BOTTOM
                    {
                        return 2;
                    }
                }
                break;
            case 3: // Rotate
                if (blockValue == enumBlock::BLK)
                {
                    if (thisTableVal == enumBlock::SPACE)
                    {
                        this->table[Y][X] = blockValue; // move the block to the empty space
                    }
                    else if (thisTableVal != enumBlock::BLK) // if not blk(2) -> if 1,3,4
                    {
                        return 1; // stop the changings
                    }
                }
                break;
            case 4: // Build Block
                if (blockValue == enumBlock::BLK) {
                    this->table[Y][X] = enumBlock::FBLK;
                }
                break;
            case 5: // HardDrop
                if (blockValue == enumBlock::BLK) {
                    if (thisTableVal == enumBlock::FBLK || thisTableVal == enumBlock::BOTTOM) {
                        this->blockObject->up();
                        return 1;
                    }
                }
                break;
            }
        }
    }
    return 0; // everything good
}

void GameTable::createBlock()
{
    srand((unsigned int)time(NULL));
    int blockSelection = 1; //  rand() % 5 + 1; // 1-5
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
    blockUpdate((int) 0); // update the block on the table
}

void GameTable::moveBlock(int inputKey)
{
    Block bkBlock(&block1);
    vector<vector<int>> bkTable;
    bkTable.resize(this->table.size(), vector<int>(this->table[0].size()));
    Backup::updateBackupBlock(this->blockObject, bkBlock); // backup the original block
    Backup::updateBackupTable(this->table, bkTable);
    blockUpdate((int)1);  // remove the block

    // Updating the block location along with the inputKey
    if (inputKey == DOWN) this->blockObject->down();
    else if (inputKey == LEFT) this->blockObject->left();
    else if (inputKey == RIGHT) this->blockObject->right();

    int upStatus = blockUpdate((int)2);
    // Now update the table with the new block location
    if (upStatus)
    {
        Backup::updateBackupTable(bkTable, this->table);
        Backup::updateBackupBlock(&bkBlock, *this->blockObject);
        if (inputKey == DOWN && upStatus == 2)
        {
            GameTable::buildBlock();
            GameTable::createBlock();
        }
    }
}

void GameTable::rotateBlock()
{
    Block bkBlock(&block1);
    vector<vector<int>> bkTable;
    bkTable.resize(this->table.size(), vector<int>(this->table[0].size()));
    Backup::updateBackupBlock(this->blockObject, bkBlock); // backup the original block
    Backup::updateBackupTable(this->table, bkTable);

    blockUpdate((int)1); // remove the block from the table
    this->blockObject->rotate(); // rotate the block
    
    if (blockUpdate((int)3)) // update the block if it is empty place
    {
        Backup::updateBackupTable(bkTable, this->table);
        Backup::updateBackupBlock(&bkBlock, *this->blockObject);
    }
}

void GameTable::buildBlock()
{
    blockUpdate((int)4);
}

void GameTable::hardDrop()
{
    int upStatus;
    blockUpdate((int)1);
    do {
        upStatus = blockUpdate((int)5);
        if (upStatus) break;
        this->blockObject->down();
    } while (true);
    // Out of the loop -> find the fblk or bottom
    GameTable::buildBlock();
    GameTable::createBlock();

}
