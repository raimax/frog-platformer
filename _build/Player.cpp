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

void Player::move(float x, float y, Map* map)
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
		if (currentJumpHeight < MAX_JUMP_HEIGHT || y > 0) {
			checkY(y, map);
		}
	}
}

void Player::checkX(float x, Map* map)
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

void Player::checkY(float y, Map* map)
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

		resetCollisionDirections();
	}
}

void Player::draw() {
	AnimationManager::playAnimation(currentAnimation, this);

	DrawText("TOP", 200, 200, 28, State.isCollidingTop ? GREEN : BLACK);
	DrawText("BOTTOM", 200, 230, 28, State.isCollidingBottom ? GREEN : BLACK);
	DrawText("LEFT ", 200, 260, 28, State.isCollidingLeft ? GREEN : BLACK);
	DrawText("RIGHT", 200, 290, 28, State.isCollidingRight ? GREEN : BLACK);
}

Player::Player(Rectangle rectangle) : GameObject(rectangle) {}

void Player::update(Map* map) {	
	updateMovement(map);

	if (ySpeed > 6.0f) {
		State.isDescending = true;
	}

	if (State.isDescending) {
		if (State.FacingDirection.right) {
			currentAnimation = "player_fall_right";
		}
		else {
			currentAnimation = "player_fall_left";
		}
	}

	if (!State.isAscending) {
		ySpeed += 1.0f;
	}

	hitBox.y += ySpeed;
	Rectangle rec = checkCollision(map->objectGroupData, hitBox);

	if (rec.width != 0) {
		updateCollisionDirections(0, ySpeed);
		hitBox.y -= ySpeed;
		while (!CheckCollisionRecs(hitBox, rec)) hitBox.y += Helper::sgn(ySpeed);
		hitBox.y -= Helper::sgn(ySpeed);
		ySpeed = 0;
		position.y = hitBox.y;
	}
	else {
		resetCollisionDirections();
	}

	if (State.isCollidingBottom) {
		currentJumpHeight = 0;
		if (jumps < 2) {
			jumps = 2;
		}
	}

	if (State.isCollidingTop) {
		currentJumpHeight = MAX_JUMP_HEIGHT;
	}

	//std::cout << "ySpeed: " << ySpeed << std::endl;
	//std::cout << "jumps: " << jumps << std::endl;
	//std::cout << "currentJumpHeight: " << currentJumpHeight << std::endl;
}

void Player::updateMovement(Map* map) {
	if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		if (!State.isAscending && !State.isDescending) {
			currentAnimation = "player_walk_left";
		}
		move(-MOVE_SPEED, 0, map);
	}
	else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
		if (!State.isAscending && !State.isDescending) {
			currentAnimation = "player_walk_right";
		}
		move(MOVE_SPEED, 0, map);
	}

	if (IsKeyDown(KEY_SPACE) && currentJumpHeight < MAX_JUMP_HEIGHT && jumps) {	
		State.isAscending = true;
		State.isDescending = false;
		ySpeed -= 1.8f;
		currentJumpHeight += 1.0f;

		if (State.FacingDirection.right) {
			currentAnimation = "player_jump_right";	
		}
		else {
			currentAnimation = "player_jump_left";
		}
	}
	else {
		State.isAscending = false;
		if (State.isCollidingBottom) {
			State.isDescending = false;
		}
	}

	if (IsKeyPressed(KEY_SPACE) && jumps) {
		ySpeed = 0;
		currentJumpHeight = 0;
	}

	if (IsKeyReleased(KEY_SPACE) && jumps) {
		jumps--;
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

void Player::addJump()
{
	jumps++;
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

void Player::updateCollisionDirections(float x, float y)
{
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
