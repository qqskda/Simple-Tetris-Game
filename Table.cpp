#include "Table.h"


using namespace std;

void GameTable::GameTableDraw()
{
    for (int row = 0; row < this->yAxis; ++row)
    {
        for (int col = 0; col < this->xAxis; ++col)
        {
            if (this->table[row][col] == enumBlock::WALL) cout << (char)178u << " ";
            else if (this->table[row][col] == enumBlock::BLK) cout << (char)254u << " ";
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
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int Y = j + this->blockObject->getY();
            int X = i + this->blockObject->getX();
            int blockValue = blockShape[rotation][i][j];

            switch (key)
            {
            case 1: // creation of the block
                this->table[Y][X] = blockValue;
                break;
            case 2: // Remove the block from the table
                if (this->table[Y][X] == enumBlock::BLK) {
                    this->table[Y][X] = enumBlock::SPACE;
                }
                break;
            case 3: // move | Rotate
                if (blockValue == 2)
                {
                    if (this->table[Y][X] == enumBlock::SPACE) 
                    {
                        this->table[Y][X] = blockValue; // move the block to the empty space
                    }
                    else if (table[Y][X] == enumBlock::WALL)
                    {
                        return 1; // stop the changings
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
    Block bkBlock(&block1);
    vector<vector<int>> bkTable;
    bkTable.resize(this->table.size(), vector<int>(this->table[0].size()));
    Backup::updateBackupBlock(this->blockObject, bkBlock); // backup the original block
    Backup::updateBackupTable(this->table, bkTable);
    blockUpdate((int)2);  // remove the block

    // Updating the block location along with the inputKey
    if (inputKey == DOWN) this->blockObject->down();
    else if (inputKey == LEFT) this->blockObject->left();
    else if (inputKey == RIGHT) this->blockObject->right();

    // Now update the table with the new block location
    if (blockUpdate((int)3))
    {
        Backup::updateBackupTable(bkTable, this->table);
        Backup::updateBackupBlock(&bkBlock, *this->blockObject);
    }
}

void GameTable::rotateBlock()
{
    Block bkBlock(&block1);
    vector<vector<int>> bkTable;
    bkTable.resize(this->table.size(), vector<int>(this->table[0].size()));
    Backup::updateBackupBlock(this->blockObject, bkBlock); // backup the original block
    Backup::updateBackupTable(this->table, bkTable);

    blockUpdate((int)2); // remove the block from the table
    this->blockObject->rotate(); // rotate the block
    
    if (blockUpdate((int)3)) // update the block if it is empty place
    {
        Backup::updateBackupTable(bkTable, this->table);
        Backup::updateBackupBlock(&bkBlock, *this->blockObject);
    }
}
