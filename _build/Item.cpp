#include "Item.h"

Item::Item(Rectangle hitBox) : GameObject(hitBox) {
	this->hitBox = hitBox;
	this->hitBox.width = 32;
	this->hitBox.height = 32;
}

void Item::onPickup(Player* player) {}

void Item::draw()
{
	if (!isClaimed && texture.id) {
		DrawTextureEx(texture, position, 0, 3.0f, WHITE);
	}

	//debug
	//DrawRectangleLinesEx(Rectangle{ hitBox.x + hitBox.width / 4, hitBox.y + hitBox.height / 4, hitBox.width, hitBox.height }, 1.0f, BLACK);
}

void Item::update(Player* player)
{
	if (CheckCollisionRecs(*player->getHitBox(), hitBox) && !isClaimed) {
		std::cout << "pickup" << std::endl;
		onPickup(player);
	}

	framesCounter++;

	if (framesCounter >= (60 * 3))
	{
		framesCounter = 0;
		isClaimed = false;
	}
}
