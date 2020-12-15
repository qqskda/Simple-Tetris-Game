// Simple Tetris Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Simple Tetris Game.h"

using namespace std;

#define TABLE_X_AXIS 20 // Tetris table x axis length
#define TABLE_Y_AXIS 30 // Tetris table y axis length

class MainMenu
{
public:
	MainMenu()
	{
        cout << "\n\n\n\n";
        cout << "\t\t"; cout << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@\n";
        cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
        cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
        cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@\n";
        cout << "\t\t"; cout << "      @       @                @       @ @ @      @             @\n";
        cout << "\t\t"; cout << "      @       @                @       @     @    @             @\n";
        cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@\n\n\n\n\n";
        cout << "\t\t"; cout << "               Press keys to start the game .\n\n\n\n\n\n\n";
        getchar(); // Waiting for the key to start the game
        system("cls"); // Clean the console window 
	}
};

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

int main(void) {
    system("mode con cols=100 lines=40"); // Console creationg cols and lines. 
    GameTable gt(TABLE_X_AXIS, TABLE_Y_AXIS); // GameTable Creation
    MainMenu(); // constructor call
    gt.GameTableDraw(); // Draw the table 
    getchar();
    return 0;
}

