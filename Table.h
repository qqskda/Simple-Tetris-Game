#pragma once
#include "Blocks.h"
#include <iostream>
#include <ctime>

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
    Block* blockObject = nullptr;
public:
    GameTable(int xAx, int yAx)
    {   
        this->xAxis = xAx;
        this->yAxis = yAx;
        for (int row = 0; row < yAx; ++row)
        {   // creating the table outline
            vector<int> rowVec;
            for (int col = 0; col < xAx; ++col)
            {
                rowVec.push_back(0);
            }
            table.push_back(rowVec);
        }

        // Draw the row: col Repetitions
        for (int col = 0; col < xAx; ++col)
        {
            table[0][col] = 1;
            table[yAx - 1][col] = enumBlock::BOTTOM;
        }
        // Draw the col: row - 2 reps (since top and bottom already drawn)
        for (int row = 1; row < yAx-1; ++row)
        {
            table[row][0] = 1;
            table[row][xAx - 1] = enumBlock::WALL;
        }
    }

    // function to draw the table
    void GameTableDraw();
    int  blockUpdate(int key); 
    void createBlock();
    void moveBlock(int inputKey);
    void rotateBlock();
    void buildBlock();
};
