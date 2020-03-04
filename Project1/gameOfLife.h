#pragma once
#include <vector>
#include <string>
template <class cellDerived>
class gameOfLife;
class cell
{
private:
	bool alive= false;
protected:
	bool nextAlive = false;
	std::string aliveSign = "*";
	std::string deadSign = ".";
	int x;
	int y;
public:
	cell(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool isAlive()
	{
		return alive;
	}
	void setAlive(bool isAlive)
	{
		alive = isAlive;
	}
	template <class cellDerived>
	void calculateNextState(gameOfLife<cellDerived> *parent) {};
	void update()
	{
		alive = nextAlive;
		return;
	}
	std::string toString()
	{
		return alive ? aliveSign : deadSign;
	}

};

template <class cellDerived>
class board
{
	int sizeX;
	int sizeY;
	std::vector<std::vector<cellDerived>> rows;
	gameOfLife<cellDerived> *parent;
public:
	void init(int x, int y, gameOfLife<cellDerived> *parent)
	{
		this->parent = parent;
		this->sizeX = x;
		this->sizeY = y;
		rows.resize(sizeX);
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				cellDerived c(i, j);
				rows.at(i).push_back(cellDerived(i,j));
			}
		}
	}
	cellDerived &get(int x, int y)
	{
		x %= sizeX;
		y %= sizeY;
		if (x < 0) x += sizeX;
		if (y < 0) y += sizeY;
		return rows.at(x).at(y);
	}
	void step()
	{
		for (std::vector<cellDerived> row : rows)
		{
			for (cellDerived &c : row)
			{
				c.calculateNextState(parent);
			}
		}
		for (std::vector<cellDerived> row : rows)
		{
			for (cellDerived &c : row)
			{
				c.update();
			}
		}
	}
	std::string toString()
	{
		std::string out;
		for (std::vector<cellDerived> &row : rows)
		{
			for (cellDerived &c : row)
			{
				out += c.toString() + " ";
			}
			out += '\n';
		}
		return out;
	}
};
template <class cellDerived>
class gameOfLife
{
	board<cellDerived> b;
public:
	std::string toString()
	{
		return b.toString();
	}
	void step()
	{
		b.step();
	}
	bool isAlive(int x, int y)
	{
		return b.get(x,y).isAlive();
	}
	void setAlive(int x, int y, bool isAlive)
	{
		b.get(x, y).setAlive(isAlive);
	}
	template <class cellDerived>
	gameOfLife() {};
	gameOfLife(int x, int y)
	{
		b.init(x, y, this);
	}
	~gameOfLife()
	{
	}
};
