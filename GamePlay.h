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
				if (nSelect == 224)
				{
					nSelect = _getch();
					switch (nSelect)
					{
					case UP:
						gt->rotateBlock(); // Rotate the block 90 degree 
						gotoxy(0, 0); // move the cursor 0,0 
						gt->GameTableDraw(); // overwrite the table 
						break;
					case DOWN: 
						gt->moveBlock(DOWN);
						gotoxy(0, 0);
						gt->GameTableDraw();
						break;
					case LEFT: 
						gt->moveBlock(LEFT);
						gotoxy(0, 0);
						gt->GameTableDraw();
						break;
					case RIGHT:
						gt->moveBlock(RIGHT);
						gotoxy(0, 0);
						gt->GameTableDraw();
						break;
					default:
						break;
					}
				}
			}
		}
	}
	~GamePlay()
	{
		delete gt; // Destructor
	}
};
