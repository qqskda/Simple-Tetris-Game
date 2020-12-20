#include "Table.h"


using namespace std;

HANDLE hConsole;
void CursorView(char show)
{
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void GameTable::GameTableDraw()
{
    for (int row = 0; row < this->yAxis; ++row)
    {
        for (int col = 0; col < this->xAxis; ++col)
        {
            if (this->table[row][col] == enumBlock::WALL || this->table[row][col] == enumBlock::BOTTOM) {
                SetConsoleTextAttribute(hConsole, 10);
                cout << (char)178u << " ";
            }
            else if (this->table[row][col] == enumBlock::BLK || this->table[row][col] == enumBlock::FBLK) {
                SetConsoleTextAttribute(hConsole, 11);
                cout << (char)254u << " ";
            }
            else if (this->table[row][col] == enumBlock::SHADOW)
            {
                SetConsoleTextAttribute(hConsole, 15);
                cout << (char)254u << " ";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "  ";
            }
        }
        cout << "\n";
    }
}

// Safeguard function
int GameTable::boundFailed(int X, int Y)
{
    if (Y < 0 || X < 0 || Y >= TABLE_Y_AXIS || X >= TABLE_X_AXIS) return 1;
    else return 0;
}

int GameTable::blockUpdate(int key)
{
    // the shape will be accessed 4*4 times -> better copy it in the given size.
    // Will the access consumes more expensive than copying the entire shape?
    auto blockShape = *this->blockObject->getShape().nth;
    int rotation = this->blockObject->getRotationCount();
    int i, j, Y, X, blockValue, thisTableVal, sX, sY, shadowTableVal;
    int currentY = this->blockObject->getY(), currentX = this->blockObject->getX();
    int shadowY = this->shadow->getY(), shadowX = this->shadow->getX();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            Y = j + currentY;
            X = i + currentX;
            sY = j + shadowY;
            sX = i + shadowX;

            if (boundFailed(X, Y)) continue;
            blockValue = blockShape[rotation][i][j];
            if (blockValue == 2)  thisTableVal = this->table[Y][X];
            switch (key)
            {
            case 0: // creation of the block
                this->table[Y][X] = blockValue;
                break;
            case 1: // Remove the block from the table
                if (blockValue == 2 && thisTableVal == enumBlock::BLK) { // if thisTableVal is block -> it has shadow below
                    this->table[Y][X] = enumBlock::SPACE;
                    this->table[sY][sX] = enumBlock::SPACE;
                }
                break;
            case 2: // move
                if (blockValue == enumBlock::BLK)
                {
                    if (thisTableVal == enumBlock::SPACE || thisTableVal == enumBlock::SHADOW)
                    {
                        this->table[Y][X] = blockValue; // move the block to the empty space 
                    }
                    else if (thisTableVal == enumBlock::WALL)
                    {
                        return 1; // stop the changings
                    }
                    else if (thisTableVal != enumBlock::BLK) // Not Space, not shadow, not Wall, Not BLK ->  FBLK, BOTTOM,
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
            case 6: // Shadow - HardDrop Variation
                if (blockValue == enumBlock::BLK) {
                    shadowTableVal = this->table[sY][sX];
                    if (shadowTableVal == enumBlock::FBLK || shadowTableVal == enumBlock::BOTTOM) {
                        this->shadow->up();
                        return 1;
                    }
                }
                break;
            case 7: // Build Shadow 
                if (blockValue == enumBlock::BLK) {
                    this->table[sY][sX] = enumBlock::SHADOW;
                }
                break;
            }
        }
    }
    return 0; // everything good
}

// Basic initialization of block and shadow.
void GameTable::createBlock()
{
    srand((unsigned int)time(NULL));
    int blockSelection = rand() % 5 + 1; // 1-5
    switch (blockSelection)
    {
    case 1:
        this->blockObject = new Block1;
        this->shadow = new Block1;
        break;
    case 2:
        this->blockObject = new Block2;
        this->shadow = new Block2;
        break;
    case 3:
        this->blockObject = new Block3;
        this->shadow = new Block3;
        break;
    case 4:
        this->blockObject = new Block4;
        this->shadow = new Block4;
        break;
    default:
        this->blockObject = new Block5;
        this->shadow = new Block5;
    }
    blockUpdate((int) 0); // update the block on the table
}

int GameTable::moveBlock(int inputKey)
{
    // Backup objects
    Block bkBlock(&block1);
    vector<vector<int>> bkTable;
    bkTable.resize(this->table.size(), vector<int>(this->table[0].size()));
    Backup::updateBackupBlock(this->blockObject, bkBlock);
    Backup::updateBackupTable(this->table, bkTable);
    
    // shadow has same coordinate when it is created
    // Update the coordinates of shadow before remove the block below
    GameTable::shadowCoordUpdate(); 

    // Remove the created block before redraw
    blockUpdate((int)1);  

    // Updating the block location along with the inputKey
    if (inputKey == DOWN) this->blockObject->down();
    else if (inputKey == LEFT) this->blockObject->left();
    else if (inputKey == RIGHT) this->blockObject->right();

    // Draw the block
    int upStatus = blockUpdate((int)2);

    // if Previous blockUpdate was not successful, use the backup Object
    if (upStatus)
    {
        Backup::updateBackupTable(bkTable, this->table);
        Backup::updateBackupBlock(&bkBlock, *this->blockObject);
        if (inputKey == DOWN && upStatus == 2)
        {
            GameTable::buildBlock();
            if (GameTable::statChecker()) return 1;
            GameTable::createBlock();
        }
    }
    // The actual block is in the right place (either failed or succeded)
    // Update the block coordinates to the shadow object and Draw
    Backup::updateBackupBlock(this->blockObject, *this->shadow);
    GameTable::shadowCoordUpdate();
    blockUpdate((int)7);
    return 0;
}

void GameTable::rotateBlock()
{
    // Backup Object Setup
    Block bkBlock(&block1);
    vector<vector<int>> bkTable;
    bkTable.resize(this->table.size(), vector<int>(this->table[0].size()));
    Backup::updateBackupBlock(this->blockObject, bkBlock);
    Backup::updateBackupTable(this->table, bkTable);

    // Remove the block before redraw
    blockUpdate((int)1); 
    this->blockObject->rotate(); // rotate the block
    
    // Apply the rotated shape to the table
    if (blockUpdate((int)3)) 
    {
        Backup::updateBackupTable(bkTable, this->table);
        Backup::updateBackupBlock(&bkBlock, *this->blockObject);
    }
    // After rotation done (failed | Succeded), draw shadow
    Backup::updateBackupBlock(this->blockObject, *this->shadow);
    GameTable::shadowCoordUpdate();
    blockUpdate((int)7);
}

// Solidify the blocks
void GameTable::buildBlock()
{
    blockUpdate((int)4);
}

int GameTable::hardDrop()
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
    if(GameTable::statChecker()) return 1;
    GameTable::createBlock();
    return 0;
}

// Check if a line is fully occupied
void GameTable::lineClean()
{
    bool isLinear;
    for (int y = END_OF_Y + 1; y < TABLE_Y_AXIS - 1; ++y) {
        isLinear = true;
        for (int x = 1; x < TABLE_X_AXIS - 1; ++x) { 
            if (this->table[y][x] != 3) {
                isLinear = false;
                break;
            }
        }
        if (isLinear) {
            for (int i = y; i > END_OF_Y - 1; --i) {
                for (int j = 1; j < TABLE_X_AXIS - 1; ++j) {
                    this->table[i][j] = this->table[i - 1][j]; // pull down the above line to the bottom
                }
            }
        }
    }
}

// Check if it is gameover
bool GameTable::statChecker()
{
    for (int x = 1; x < TABLE_X_AXIS - 1; ++x) {
        if (table[END_OF_Y][x] == enumBlock::FBLK) return true;
    }
    return false;
}

void GameTable::shadowCoordUpdate()
{
    int shadowStat;
    do {
        shadowStat = blockUpdate((int)6);
        if (shadowStat) break;
        this->shadow->down();
    } while (true);
}
