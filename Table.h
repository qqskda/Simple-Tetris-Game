#pragma once
#include "Blocks.h"

#define LEFT 75
#define RIGHT 77 
#define UP 72
#define DOWN 80

using namespace std;

class GameTable
{
private:
    int xAxis = 0;
    int yAxis = 0;
    vector<vector<int>> table; // game table
    Block* blockObject = new Block1;
public:
    GameTable(int xAx, int yAx)
    {   
        xAxis = xAx;
        yAxis = yAx;
        for (int row = 0; row < yAxis; ++row)
        {   // creating the table outline
            vector<int> rowVec;
            for (int j = 0; j < xAxis; j++)
            {
                rowVec.push_back(0);
            }
            table.push_back(rowVec);
        }

        for (int col = 0; col < xAxis; ++col)
        {
            table[0][col] = 1;
            table[yAxis - 1][col] = 1;
        }

        for (int row = 0; row < yAxis; ++row)
        {
            table[row][0] = 1;
            table[row][xAxis - 1] = 1;
        }
    }

    // function to draw the table
    void GameTableDraw();
    void blockUpdate(int key); // 0: newUpdate, 2: Remove Block, 1: first update
    void createBlock();
    void moveBlock(int inputKey);
    void rotateBlock();
};
