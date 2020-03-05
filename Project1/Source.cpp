#include <iostream>
#include "gameOfLife.h"

class myCell : public cell
{
public:
	void calculateNextState(gameOfLife<myCell> *parent)
	{
		int aliveNeighbours = 0;
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if ((x!=i || y!=j) &&parent->isAlive(i, j)) aliveNeighbours++;
			}
		}
		if (this->isAlive())
		{
			if (aliveNeighbours == 2 || aliveNeighbours == 3) 
				nextAlive = true;
			else nextAlive = false;
		}
		else if (aliveNeighbours == 3)
		{
			nextAlive = true;
		}
		else nextAlive = false;
	}
	myCell(int x, int y) : cell(x,y)
	{
		aliveSign = "O";
	}
};
int main()
{
	gameOfLife<myCell> game(10,10);
	game.setAlive(3, 1, true);
	game.setAlive(3, 2, true);
	game.setAlive(3, 3, true);
	game.setAlive(2, 3, true);
	game.setAlive(1, 2, true);
	while (true)
	{
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		std::cout << game.toString();
		game.step();
		std::cin.ignore();
	}
}