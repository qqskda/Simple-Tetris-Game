#pragma once

#include <Windows.h>
#include <vector>
using namespace std;

#define TABLE_X_AXIS 20 // Tetris table x axis length
#define TABLE_Y_AXIS 38 // Tetris table y axis length

// Blocks enum
enum enumBlock
{
    SPACE = 0,   // Empty Space
    WALL = 1,    // Wall - Boudary
    BLK = 2,     // Block
    FBLK = 3,    // Finished Block = Built
    BOTTOM = 4,  // Bottom Boundary

};

// Cursor invisible 0, visible 1
void CursorView(char show);

// Cursor Position
void gotoxy(short x, short y);

// Shape: pass the pointer
struct Shape {
    const int (*nth)[4][4][4]; // pointer to const int [4][4][4]
};

// 1st block
const int block1[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {2, 2, 2, 2},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {2, 2, 2, 2},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0}
        }

};
// 2nd block
const int block2[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        }

};
// 3rd blcok
const int block3[4][4][4] = {
        {
                        {0, 2, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 2},
                        {0, 2, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 2, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 0, 2, 0},
                        {2, 2, 2, 0},
                        {0, 0, 0, 0}

        }

};
// 4th block
const int block4[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {2, 2, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {2, 2, 0, 0},
                        {0, 0, 0, 0}

        }

};
// 5th block
const int block5[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 2},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 2, 0},
                        {0, 2, 2, 2},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 2},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}

        }

};



class Block
{
protected:
    Shape shape;
    int x = ((int)TABLE_X_AXIS / 2) - 3; // Centre
    int y = 1;
    int rotationCount = 0; // 0 - 3
public:
    Block(const int (*bkNum)[4][4][4]);

    int getX()
    {
        return this->x;
    }
    int getY()
    {
        return this->y;
    }
    int getRotationCount() {
        return this->rotationCount;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    void setRotation(int rotation);
    void down();
    void left();
    void right();
    void rotate();
    void up();
    void setShape(Shape givenShape);
    Shape getShape(){
        return this->shape;
    }
};

// Backup functions used to swap between the origin and backup components
// Switch the order of input upon needs
class Backup
{
public:
    static void updateBackupBlock(Block* origin, Block& backupBlock);
    // Each table is required to be in the same size before calling the function to avoid unnecessary resize
    static void updateBackupTable(vector<vector<int>>& origin, vector<vector<int>>& backupTable);
};

class Block1 : public Block {
public:
    Block1() : Block::Block(&block1) {}
};

class Block2 : public Block {
public:
    Block2() : Block::Block(&block2) {}
};
class Block3 : public Block {
public:
    Block3() : Block::Block(&block3) {}
};
class Block4 : public Block {
public:
    Block4() : Block::Block(&block4) {}
};
class Block5 : public Block {
public:
    Block5() : Block::Block(&block5) {}
};;
