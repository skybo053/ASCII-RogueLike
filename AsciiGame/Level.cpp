#include "Level.h"


Level::Level(int rows, int cols, ifstream& level) : rows(rows), cols(cols), level(level)
{
	//init class variables
	map = new char*[rows];
	srand(time(NULL));
	exit = false;
	playerDied = false;
	hasEnemy = false;

	for (int i = 0; i < rows; i++)
		map[i] = new char[cols];


	//init level
	string levelString;

	for (int i = 0; i < rows; i++) {
		getline(level, levelString);

		for (int j = 0; j < cols; j++) {
			if (j > levelString.length()) {
				map[i][j] = ' ';
			}
			else
				map[i][j] = levelString[j];
		}
	}

	getPlayerCoords();
	getEnemyCoords();
}


void Level::movePlayer(char move, Player& player) {
	p = player;
	char lcMove = std::tolower(move);

	switch (lcMove) {

	case 'w':
		updateCharacter(-1, 0, player, lcMove);
		if (hasEnemy) {
			for (int i = 0; i < enemies.size(); ++i) {
				enemies[i].moveEnemy(*this);
			}
		}
		break;

	case 's':
		updateCharacter(1, 0, player, lcMove);
		if (hasEnemy) {
			for (int i = 0; i < enemies.size(); ++i) {
				enemies[i].moveEnemy(*this);
			}
		}
		break;

	case 'a':
		updateCharacter(0, -1, player, lcMove);
		if (hasEnemy) {
			for (int i = 0; i < enemies.size(); ++i) {
				enemies[i].moveEnemy(*this);
			}
		}
		break;

	case 'd':
		updateCharacter(0, 1, player, lcMove);
		if (hasEnemy) {
			for (int i = 0; i < enemies.size(); ++i) {
				enemies[i].moveEnemy(*this);
			}
		}
		break;

	case 'p':
		exit = true;
		cout << "skipping level" << endl;
		break;

	}

}



void Level::updateCharacter(int r, int c, Player& player, char lcMove) {
	//Checking if wall collision
	if (map[rowMove + r][colMove + c] == '#') {
		cout << "There is a wall there!!" << endl;
		return;
	}

	//Checking if key pickup
	if (map[rowMove + r][colMove + c] == '>') {
		player.setKey(1);
		p.setKey(1);
		cout << "You got a key!" << endl;
		map[rowMove][colMove] = '-';
		rowMove += r;
		colMove += c;
		map[rowMove][colMove] = '@';
		return;
	}

	//checking if door collision with no keys
	if (map[rowMove + r][colMove + c] == '+' && player.getKey() <= 0) {
		cout << "You need a key to open this door!" << endl;
		return;
	}

	//checking if door collision with keys
	if (map[rowMove + r][colMove + c] == '+' && player.getKey() > 0) {
		player.setKey(-1);
		p.setKey(-1);
		cout << "You opened the door!  You have " << player.getKey() << " keys left." << endl;
		map[rowMove][colMove] = '-';
		rowMove += r;
		colMove += c;
		map[rowMove][colMove] = '@';
		return;
	}

	//checking if Exiting level
	if (map[rowMove + r][colMove + c] == 'O') {
		exit = true;
		cout << "You found the exit!" << endl;
		map[rowMove][colMove] = '-';
		rowMove += r;
		colMove += c;
		map[rowMove][colMove] = 'O';
		return;

	}

	//printing directions
	if (lcMove == 'a') {
		cout << "West!" << endl;
	}
	if (lcMove == 'w') {
		cout << "North!" << endl;
	}
	if (lcMove == 'd') {
		cout << "East!" << endl;
	}
	if (lcMove == 's') {
		cout << "South!" << endl;
	}

	map[rowMove][colMove] = '-';

	rowMove += r;
	colMove += c;

	map[rowMove][colMove] = '@';

}

void Level::getPlayerCoords() {
	bool found = false;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == '@') {
				found = true;
				rowMove = i;
				colMove = j;
				break;
			}
		}
		if (found)
			return;
	}
}

void Level::getEnemyCoords() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (map[i][j] == '*') {
				if (!hasEnemy)
					hasEnemy = true;
				
				enemies.push_back(Enemy(i, j));
			}
		}
	}
}


void Level::printKey() {
	cout << "W - up";          cout << std::setw(44) << "Player = @";
	cout << "\nS - down";      cout << std::setw(40) << "Wall = #";
	cout << "\nA - left";      cout << std::setw(40) << "Door = +";
	cout << "\nD - right";     cout << std::setw(38) << "Key = >";
	cout << endl;

	if (hasEnemy)
		cout << std::setw(49) << "Enemy = *" << endl;

	cout << "Player inventory:";  cout << std::setw(31) << "Exit = O";
	cout << endl;
	((p.hasInventory()) ? cout << "Keys x " << p.getKey() : cout << "[empty]") << endl;

}

void Level::printLevel() {
	//cout << "columns: " << cols << endl;
	//cout << "rows: " << rows << endl << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool Level::getExit() const { return exit; }

bool Level::getHasEnemy() const { return hasEnemy; }

int Level::getPlayerRow() const { return rowMove; }

int Level::getPlayerCol() const { return colMove; }

bool Level::getPlayerDied() const { return playerDied; }


Level::~Level() {
	for (int i = 0; i < rows; i++) {
		delete[] map[i];
	}
	delete map;
}
