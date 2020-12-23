// Simple Tetris Game.cpp : Defines the entry point for the application.
//

#include "header/framework.h"
#include "header/Simple Tetris Game.h"
#include "header/Table.h"
#include "header/Blocks.h"
#include "header/GamePlay.h"

using namespace std;

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

// Allow user to restart | exit the game
int exitContinue()
{
    system("cls");
    cout << "GAME OVER!" << endl;
    cout << "'r' to Restart the game | 'e' to Exit the game" << endl;
    int nSelect;
    do {
        if (_kbhit())
        {
            nSelect = _getch();
            if (nSelect == EXIT) {
                return 0;
            }
            else if (nSelect == RESTART) {
                return 1;
            }
            else {
                cout << "Please enter either 'r' or 'e'" << endl;
            }
        }
    } while (true);
    return 0;
}

int wmain(void) {
    int nextCommand = 0;
    CursorView(false);
    system("mode con cols=100 lines=40");       // Console creationg cols and lines.
    GameTable gt(TABLE_X_AXIS, TABLE_Y_AXIS);   // GameTable Creation
    do {
        MainMenu();                             // MainMenu constructor call
        GamePlay gp = GamePlay();               // GamePlay constructor -> Start of the game
        nextCommand = exitContinue();           // Called after the gameover
    } while (nextCommand);                      // Exit the loop when play chose to exit
    getchar();
    return 0;
}

