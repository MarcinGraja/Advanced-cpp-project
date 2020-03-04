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
		//if (x >= 0 && x <= 2 && y >= 0 && y <= 2) 
			std::cout << x << ";" << y << ":" << "alive: " << isAlive() << " next alive: " << nextAlive << " alive neigbours: " << aliveNeighbours << '\n';
	}
	myCell(int x, int y) : cell(x,y)
	{
	}
};
int main()
{
	gameOfLife<myCell> game(5,5);
	game.setAlive(2, 1, true);
	game.setAlive(2, 2, true);
	game.setAlive(2, 3, true);
	while (true)
	{
		std::cout << game.toString();
		game.step();
		std::cin.ignore();
	}
}