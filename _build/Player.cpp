#include "Player.h"
#include <iostream>
#include <math.h>

void Player::setFacingDirection(Direction direction)
{
	switch (direction)
	{
	case LEFT:
		State.FacingDirection.left = true;
		State.FacingDirection.right = false;
		break;
	case RIGHT:
		State.FacingDirection.left = false;
		State.FacingDirection.right = true;
		break;
	default:
		break;
	}
}

void Player::move(int x, int y, Map* map)
{
	if (x > 0) {
		setFacingDirection(RIGHT);
	}
	else if (x < 0) {
		setFacingDirection(LEFT);
	}

	if (x != 0) {
		checkX(x, map);
	}
	if (y != 0) {
		checkY(y, map);
	}
}

void Player::checkX(int x, Map* map)
{
	hitBox.x += x;
	Rectangle rec = checkCollision(map->objectGroupData, hitBox);

	if (rec.width != 0) {
		
		hitBox.x -= x;
		while (!CheckCollisionRecs(hitBox, rec)) hitBox.x += Helper::sgn(x);
		hitBox.x -= Helper::sgn(x);
		position.x = hitBox.x;
	}
	else {
		position.x += x;
		
	}
}

void Player::checkY(int y, Map* map)
{
	hitBox.y += y;
	Rectangle rec = checkCollision(map->objectGroupData, hitBox);

	if (rec.width != 0) {
		updateCollisionDirections(0, y);
		hitBox.y -= y;
		while (!CheckCollisionRecs(hitBox, rec)) hitBox.y += Helper::sgn(y);
		hitBox.y -= Helper::sgn(y);
		position.y = hitBox.y;
	}
	else {
		position.y += y;
		currentJumpHeight += 0.2f;
	}
}

void Player::draw() {
	AnimationManager::playAnimation(currentAnimation, this);
}

Player::Player(Rectangle rectangle) : GameObject(rectangle) {}

void Player::update(Map* map) {	
	updateMovement(map);

	move(0, 7.0f, map);

	position.x += xSpeed;
	position.y += ySpeed;

	hitBox.x = position.x;
	hitBox.y = position.y;

	std::cout << "col top: " << State.isCollidingTop << std::endl;
	std::cout << "col bot: " << State.isCollidingBottom << std::endl;
	std::cout << "col left: " << State.isCollidingLeft << std::endl;
	std::cout << "col right: " << State.isCollidingRight << std::endl;
}

void Player::updateMovement(Map* map) {
	if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		currentAnimation = "player_walk_left";
		move(-8.0f, 0, map);
	}
	else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
		currentAnimation = "player_walk_right";
		move(8.0f, 0, map);
	}

	if (IsKeyDown(KEY_SPACE)) {
		if (State.FacingDirection.right) {
			currentAnimation = "player_jump_right";
		}
		else {
			currentAnimation = "player_jump_left";
		}
		move(0, -14.0f, map);
	}

	if (!IsKeyDown(KEY_SPACE) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		if (State.FacingDirection.right) {
			currentAnimation = "player_idle_right";
		}
		else {
			currentAnimation = "player_idle_left";
		}
	}
}

Player::ObjectState Player::getState()
{
	return State;
}

Rectangle Player::checkCollision(std::vector<ObjectGroupData>& objectGroupData, Rectangle hitBox) {
	for (auto const& objectGroup : objectGroupData) {
		if (objectGroup.id == COLLISION) {
			for (auto const& object : objectGroup.objects) {
				if (CheckCollisionRecs(hitBox, object.rectangle)) {
					return object.rectangle;
				}
			}
		}
	}

	return Rectangle{ 0 };
}

void Player::updateCollisionDirections(int x, int y)
{
	State.isCollidingTop = false;
	State.isCollidingBottom = false;
	State.isCollidingLeft = false;
	State.isCollidingRight = false;

	/*std::cout << "x: " << x << std::endl;*/
	std::cout << "y: " << y << std::endl;

	if (x > 0) {
		State.isCollidingRight = true;
	}
	else if (x < 0) {
		State.isCollidingLeft = true;
	}
	else if (y > 0) {
		State.isCollidingBottom = true;
	}
	else if (y < 0) {
		State.isCollidingTop = true;
	}
}

void Player::resetCollisionDirections()
{
	State.isCollidingTop = false;
	State.isCollidingBottom = false;
	State.isCollidingLeft = false;
	State.isCollidingRight = false;
}
