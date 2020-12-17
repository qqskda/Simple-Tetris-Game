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



int wmain(void) {
    
    CursorView(false);
    system("mode con cols=100 lines=40"); // Console creationg cols and lines. 
    GameTable gt(TABLE_X_AXIS, TABLE_Y_AXIS); // GameTable Creation
    MainMenu(); // constructor call
    GamePlay gp = GamePlay();
    int b = getchar();
    return 0;
}

