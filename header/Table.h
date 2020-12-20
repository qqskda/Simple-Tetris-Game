#pragma once
#include "Blocks.h"
#include <iostream>
#include <ctime>

// Keyboard Input
#define LEFT 75
#define RIGHT 77 
#define UP 72
#define DOWN 80 
#define HARD 32

// Player Options - After gameover
#define RESTART 114
#define EXIT 101

// GameOver indicator
#define END_OF_Y 2

using namespace std;

// Cursor invisible 0, visible 1
void CursorView(char show);


class GameTable
{
private:
    int xAxis = 0;
    int yAxis = 0;
    vector<vector<int>> table;
    Block* blockObject = nullptr;
    Block* shadow = nullptr;

public:
    GameTable(int xAx, int yAx)
    {   
        this->xAxis = xAx;
        this->yAxis = yAx;
        // Creating the table format
        for (int row = 0; row < yAx; ++row)
        { 
            vector<int> rowVec;
            for (int col = 0; col < xAx; ++col)
            {
                rowVec.push_back(0);
            }
            table.push_back(rowVec);
        }

        // Draw the row: Top and Bottom
        for (int col = 0; col < xAx; ++col)
        {
            table[0][col] = enumBlock::WALL;;
            table[yAx - 1][col] = enumBlock::BOTTOM;
        }
        // Draw the col: Left and Right boundary (row - 2 reps as Top and Bottom already Drawn)
        for (int row = 1; row < yAx-1; ++row)
        {
            table[row][0] = enumBlock::WALL;
            table[row][xAx - 1] = enumBlock::WALL;
        }
    }
    
    void GameTableDraw();
    int  blockUpdate(int key); 
    void createBlock();
    int moveBlock(int inputKey);
    void rotateBlock();
    // Once confirmed the block drops completed
    void buildBlock();
    // Fast Drop to the bottom
    int hardDrop();
    // Safeguard function
    int boundFailed(int X, int Y);
    // Remove the line 
    void lineClean();
    bool statChecker();
    void shadowCoordUpdate();
};
