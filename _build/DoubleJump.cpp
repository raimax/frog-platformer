#include "DoubleJump.h"
#include "./SpriteManager.h"

DoubleJump::DoubleJump(Rectangle hitBox) : Item(hitBox) 
{
	texture = SpriteManager::item["double_jump"];
}

void DoubleJump::onPickup(Player* player)
{
	player->addJump();
	isClaimed = true;
}
