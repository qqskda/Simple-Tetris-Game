// Simple Tetris Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Simple Tetris Game.h"
#include "Table.h"
#include "Blocks.h"
#include "GamePlay.h"

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
        int a = getchar(); // Waiting for the key to start the game
        system("cls"); // Clean the console window 
	}
};

// Allow user to restart | exit the game
int exitContinue()
{
    system("cls");
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
    system("mode con cols=100 lines=40"); // Console creationg cols and lines. 
    GameTable gt(TABLE_X_AXIS, TABLE_Y_AXIS); // GameTable Creation
    do {
        MainMenu(); // constructor call
        GamePlay gp = GamePlay();
        nextCommand = exitContinue();
    } while (nextCommand > 0);
    getchar();
    return 0;
}

