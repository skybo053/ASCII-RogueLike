#define NUM_LEVELS 3
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cctype>


#include "Level.h"
#include "Player.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::ios;

//function prototypes
void initLevels();
void columnNum(string, ifstream&);
void rowNum(string, ifstream&);


//Global variables
int cols;
int rows;
string fileString;
Player player;
Level *levels[NUM_LEVELS];

int main() {
	char move;
	initLevels();


	for (int i = 0; i < NUM_LEVELS; i++) {
		cout << "Level " << i + 1 << endl;
		levels[i]->printLevel();
		levels[i]->printKey();

		while (true) {

			cout << "\nEnter direction: ";
			move = _getch();


			if (move != 'w' && move != 'd' && move != 'a' && move != 's' && move != 'p') {
				cout << "Key not recognized";
				continue;
			}

			system("cls");
			levels[i]->movePlayer(move, player);
			levels[i]->printLevel();
			levels[i]->printKey();

			//Check if player exited and it was the last level
			if (levels[i]->getExit() && i == NUM_LEVELS - 1) {
				system("cls");
				cout << "**************YOU HAVE ESCAPED THE DUNGEON! *************" << endl;
				cout << "****************** Congratulations!!! *******************" << endl;
				cin.get();
				break;
			}

			//Check if player exited
			if (levels[i]->getExit()) {
				cout << "\nYou escaped Level " << i+1 << "!  Congratulations!" << endl << endl;
				delete levels[i];
				system("pause");
				system("cls");
				break;
			}
			//Check if player died
			if (levels[i]->getPlayerDied()) {
				cout << "\n************ YOU HAVE BEEN KILLED BY AN ENEMY! ************" << endl;
				delete levels[i];
				i = NUM_LEVELS;
				break;
			}
			
			
		}//end while loop
		
	} // end for loop 


	cout << "\nGame Over...";
	cin.get();
	return 0;
}


void initLevels() {
	string files[NUM_LEVELS];
	files[0] = "Level1.txt";
	files[1] = "Level2.txt";
	files[2] = "Level3.txt";

	for (int i = 0; i < NUM_LEVELS; i++) {
		
		ifstream input(files[i]);
		columnNum(fileString, input);
		rowNum(fileString, input);
		levels[i] = new Level(rows, cols, input);
		input.close();
	}

}


void columnNum(string fileString, ifstream& file) {

	cols = 0;
	while (getline(file, fileString)) {
		int i = 1;
		for (; i < fileString.length(); i++); //looping through single line of text
		if (i > cols) {
			cols = i;
		}
	}
	//reset file pointer
	file.clear();
	file.seekg(0, ios::beg);
}



void rowNum(string fileString, ifstream& file) {

	rows = 0;
	while (getline(file, fileString)) {
		rows++;
	}

	//reset file pointer
	file.clear();
	file.seekg(0, ios::beg);
}


