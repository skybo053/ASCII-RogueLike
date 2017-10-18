#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	Player();
	bool hasInventory();
	void setKey(int num);
	int getKey() const;
	
	~Player();
private:
	int key;
};

#endif
