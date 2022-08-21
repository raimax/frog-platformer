#pragma once
#include "Item.h"

class DoubleJump : public Item
{
private:
	void onPickup(Player* player) override;
public:
	DoubleJump(Rectangle hitBox);
};

