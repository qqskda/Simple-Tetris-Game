#pragma once

#include <Windows.h>
#include <vector>
using namespace std;

#define TABLE_X_AXIS 20 // Tetris table x axis length
#define TABLE_Y_AXIS 38 // Tetris table y axis length

// Cursor invisible 0, visible 1
void CursorView(char show);

// Cursor Position
void gotoxy(short x, short y);

// Shape Data Structure
struct Shape {
    int nth;
    int rotation;
};

vector<const int[4][4][4]> vecBlocks;
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

vecBlocks.push_back(block1);

class Block
{
protected:
    Shape shape;
    int x = ((int)TABLE_X_AXIS / 2) - 3; // Centre
    int y = 1;
    int rotationCount = 0; // 0 - 3
public:
    Block(int rotate, int bkNum);

    Shape getShape(int nth, int rotation)
    {
        Shape output = { nth, rotation };
        return output;
    }
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
    void setShape(Shape givenShape);
    Shape getShape(){
        return this->shape;
    }
};

class Backup
{
public:
    static void updateBackupBlock(Block* origin, Block& backupBlock);
    static void updateBackupTable(vector<vector<int>>& origin, vector<vector<int>>& backupTable);
    static void restoreOriginTable(vector<vector<int>>& origin, vector<vector<int>>& backupTable);
};

class Block1 : public Block {
public:
    Block1() : Block::Block((int) 0, (int) 0) {}
};

class Block2 : public Block {
public:
    Block2() : Block::Block((int)0, (int)0) {}
};
class Block3 : public Block {
public:
    Block3() : Block::Block((int)0, (int)0) {}
};
class Block4 : public Block {
public:
    Block4() : Block::Block((int)0, (int)0) {}
};
class Block5 : public Block {
public:
    Block5() : Block::Block((int)0, (int)0) {}
};;
