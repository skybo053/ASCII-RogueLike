#ifndef LEVEL_H
#define LEVEL_H



#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <vector>

#include "Enemy.h"
#include "Player.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

// Not sure if need forward class declaration for enemy class.  Works sometimes without
class Enemy;

class Level
{
public:
	Level(int rows, int cols, ifstream& level);
	void printLevel();
	void printKey();
	void movePlayer(char move, Player& player);
	void updateCharacter(int moveX, int moveY, Player& player, char lcMove);
	
	
	//getters

	char** getMap() { return map; }
	bool getExit() const;
	bool getPlayerDied() const;
	bool getHasEnemy() const;
	int getPlayerRow() const;
	int getPlayerCol() const;

	//setters
	void setPlayerDied(bool b) { playerDied = b; }

	~Level();

private:
	void getPlayerCoords();
	void getEnemyCoords();

	//variables for total rows and columns in a level object
	int rows, cols;

	//variables to hold player position in level
	int rowMove, colMove;


	ifstream& level;
	char** map;
	Player p;
	bool exit, hasEnemy, playerDied;

	//holding enemy objects
	vector<Enemy> enemies;

	

};

#endif