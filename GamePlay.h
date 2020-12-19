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
		while (true)
		{
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
						gt->moveBlock(DOWN);
						break;
					case LEFT: 
						gt->moveBlock(LEFT);
						break;
					case RIGHT:
						gt->moveBlock(RIGHT);
						break;
					default:
						break;
					}
				}
				else if (nSelect = HARD)
				{
					gt->hardDrop();
				}
			}
			gotoxy(0, 0);
			gt->GameTableDraw();
		}
	}
	~GamePlay()
	{
		delete gt; // Destructor
	}
};
