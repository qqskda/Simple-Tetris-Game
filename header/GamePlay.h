#pragma once
#include "Table.h"
#include <conio.h>

class GamePlay
{
private:
	GameTable* gt;
public:
	GamePlay() // constructor
	{
		gt = new GameTable(TABLE_X_AXIS, TABLE_Y_AXIS);
		gt->createBlock(); // default block creation
		gt->GameTableDraw(); // draw the gametable
		int isOver = 0;
		int timer = 0;
		clock_t start, end;
		start = clock();
		float time;
		while (true)
		{
			end = clock();
			time = ((float)end - start) / CLOCKS_PER_SEC;
			if (time > 1.5) // every 1.5 secs, move the block down.
			{
				isOver = gt->moveBlock(DOWN);
				start = clock();
			}
			int nSelect;
			if (_kbhit())
			{
				nSelect = _getch();
				if (nSelect == 224) // Arrow Keys follow after 224.
				{
					nSelect = _getch();
					switch (nSelect)
					{
					case UP:
						gt->rotateBlock(); // Rotate the block 90 degree 
						break;
					case DOWN: 
						isOver = gt->moveBlock(DOWN);
						break;
					case LEFT: 
						isOver = gt->moveBlock(LEFT);
						break;
					case RIGHT:
						isOver = gt->moveBlock(RIGHT);
						break;
					default:
						break;
					}
				}
				else if (nSelect == HARD)
				{
					isOver = gt->hardDrop();
				}
			}
			if (isOver) return; // Game Over
			gt->lineClean();
			gotoxy(0, 0);
			gt->GameTableDraw(); // draw the gametable
		}
	}
	// Destructor called when player exit the game
	~GamePlay()
	{
		system("cls");
		gotoxy(10, 10);
		cout << "Thanks for playing the game!" << endl;
		delete gt; // Destructor
	}
};
