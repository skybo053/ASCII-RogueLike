#ifndef ENEMY_H
#define ENEMY_H

#include <random>
#include "Level.h"

class Level;


class Enemy {
public:
	Enemy();
	Enemy(int row, int col);

	void moveEnemy(Level &level);

	~Enemy();

	//getters
	int getRow()  const;
	int getCol() const;

	//setters();
	void setRow(int row);
	void setCol(int col);

private:
	int row;
	int col;

};

#endif