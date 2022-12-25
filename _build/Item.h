#pragma once
#include "Player.h"

class Item : GameObject
{
protected:
	bool isClaimed = false;
	virtual void onPickup(Player* player);
	Rectangle getCenter();
	Texture2D texture;
	int framesCounter = 0;
public:
	Item(Rectangle hitBox);
	void draw() override;
	void update(Player* player);
	void reset();
};

