#pragma once

using namespace std;

class GameTable
{
private:
    int xAxis;
    int yAxis;
    vector<vector<int>> table; // game table
public:
    GameTable(int xAxis, int yAxis)
    {
        this->xAxis = xAxis;
        this->yAxis = yAxis;
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
    void GameTableDraw()
    {
        for (int row = 0; row < yAxis; ++row)
        {
            for (int col = 0; col < xAxis; ++col)
            {
                if (table[row][col] == 1) cout << "**";
                else cout << "  ";
            }
            cout << "\n";
        }
    }

};
