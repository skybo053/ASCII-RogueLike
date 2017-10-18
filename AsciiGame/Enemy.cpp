#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(int row, int col) : row(row), col(col) {}



void Enemy::moveEnemy(Level &level) { 
	
	bool moved = false;
	int direction = rand() % 4;
	char** map = level.getMap();
	
	int eRow = this->getRow();
	int eCol = this->getCol();

		while (moved != true) {

			switch (direction) {

			case 0: //////////////up
				if (map[eRow - 1][eCol] != '-' && map[eRow - 1][eCol] != '@') {
					direction = rand() % 4;
					break;
				}
				else {
					//if spot where enemy just was is now occupied by player, don't write over
					if (map[eRow][eCol] == '@') {
						this->setRow(eRow -= 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
					else {
						map[eRow][eCol] = '-';
						this->setRow(eRow -= 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
				}

			case 1: ///////////////right
				if (map[eRow][eCol + 1] != '-' && map[eRow][eCol + 1] != '@') {
					direction = rand() % 4;
					break;
				}
				else {
					if (map[eRow][eCol] == '@') {
						this->setCol(eCol += 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
					else {
						map[eRow][eCol] = '-';
						this->setCol(eCol += 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
				}

			case 2: ////////////////down
				if (map[eRow + 1][eCol] != '-' && map[eRow + 1][eCol] != '@') {
					direction = rand() % 4;
					break;
				}
				else {
					if (map[eRow][eCol] == '@') {
						this->setRow(eRow += 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
					else {
						map[eRow][eCol] = '-';
						this->setRow(eRow += 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
				}

			case 3: ////////////////left
				if (map[eRow][eCol - 1] != '-' && map[eRow][eCol - 1] != '@') {
					direction = rand() % 4;
					break;
				}
				else {
					if (map[eRow][eCol] == '@') {
						this->setCol(eCol -= 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
					else {
						map[eRow][eCol] = '-';
						this->setCol(eCol -= 1);
						map[eRow][eCol] = '*';
						moved = true;
						break;
					}
				}
			} // end switch
		} // end while loop
		moved = false;

		if (eCol == level.getPlayerCol() && eRow == level.getPlayerRow()) { // check if enemy is on same tile as player; player dies
			level.setPlayerDied(true);
		}

	

}//end enemyMove method




//getters
int Enemy::getRow()  const { return row; }
int Enemy::getCol() const { return col; }

//setters
void Enemy::setRow(int row) { this->row = row; }
void Enemy::setCol(int col) { this->col = col; }


Enemy::~Enemy()
{
}
