#include "Player.h"
#include <iostream>

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

void Player::move(Direction direction, Map* map)
{
	setFacingDirection(direction);

	switch (direction)
	{
	case LEFT:
		xSpeed--;
		if (State.isAscending) {
			if (State.FacingDirection.left) {
				currentAnimation = "player_jump_left";
			}
			else {
				currentAnimation = "player_jump_right";
			}
			break;
		}
		else if (State.isDescending) {
			if (State.FacingDirection.left) {
				currentAnimation = "player_fall_left";
			}
			else {
				currentAnimation = "player_fall_right";
			}
			break;
		};
		currentAnimation = "player_walk_left";
		break;
	case RIGHT:
		xSpeed++;
		if (State.isAscending) {
			if (State.FacingDirection.left) {
				currentAnimation = "player_jump_left";
			}
			else {
				currentAnimation = "player_jump_right";
			}
			break;
		}
		else if (State.isDescending) {
			if (State.FacingDirection.left) {
				currentAnimation = "player_fall_left";
			}
			else {
				currentAnimation = "player_fall_right";
			}
			break;
		};
		currentAnimation = "player_walk_right";
		break;
	case UP:
		State.isAscending = true;
		hitBox.y++;
		if (checkCollision(map->objectGroupData, hitBox)) {
			ySpeed = MAX_JUMP_HEIGHT;
		}
		hitBox.y--;
		if (State.isAscending) {
			if (State.FacingDirection.left) {
				currentAnimation = "player_jump_left";
			}
			else {
				currentAnimation = "player_jump_right";
			}
		}
		if (State.isDescending) {
			if (State.FacingDirection.left) {
				currentAnimation = "player_fall_left";
			}
			else {
				currentAnimation = "player_fall_right";
			}
		};
		break;
	case IDLE:
		if (State.FacingDirection.left) {
			currentAnimation = "player_idle_left";
		}
		else {
			currentAnimation = "player_idle_right";
		}
		break;
	default:
		break;
	}
}

void Player::draw() {
	AnimationManager::playAnimation(currentAnimation, this);
}

Player::Player(Rectangle rectangle) : GameObject(rectangle) {}

void Player::update(Map* map) {
	updateMovement(map);

	if (ySpeed == 0) {
		State.isAscending = false;
		State.isDescending = false;
	}
	else if (ySpeed == MAX_JUMP_HEIGHT) {
		State.isDescending = true;
	}

	if (State.isAscending) {
		State.isDescending = false;
	}

	if (State.isDescending) {
		State.isAscending = false;
	}

	if (xSpeed > 0 && xSpeed < 0.75) xSpeed = 0;
	if (xSpeed < 0 && xSpeed > -0.75) xSpeed = 0;

	if (xSpeed > xMaxSpeed) xSpeed = xMaxSpeed;
	if (xSpeed < -xMaxSpeed) xSpeed = -xMaxSpeed;

	ySpeed += 0.3f;

	//horizontal collision
	hitBox.x += xSpeed;
	if (checkCollision(map->objectGroupData, hitBox)) {
		hitBox.x -= xSpeed;
		while (!checkCollision(map->objectGroupData, hitBox)) hitBox.x += Helper::sgn(xSpeed);
		hitBox.x -= Helper::sgn(xSpeed);
		xSpeed = 0;
		position.x = hitBox.x;
	}
	//vertical collision
	hitBox.y += ySpeed;
	if (checkCollision(map->objectGroupData, hitBox)) {
		hitBox.y -= ySpeed;
		while (!checkCollision(map->objectGroupData, hitBox)) hitBox.y += Helper::sgn(ySpeed);
		hitBox.y -= Helper::sgn(ySpeed);
		ySpeed = 0;
		position.y = hitBox.y;
	}

	position.x += xSpeed;
	position.y += ySpeed;

	hitBox.x = position.x;
	hitBox.y = position.y;
}

void Player::updateMovement(Map* map) {
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) || !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		// slow down gradually
		xSpeed *= 0.8f;
	}
	
	if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		move(LEFT, map);
	}
	else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
		move(RIGHT, map);
	}
	else if (!State.isAscending && !State.isDescending) {
		move(IDLE, map);
	}

	if (IsKeyPressed(KEY_SPACE)) {
		move(UP, map);
	}
}

Player::ObjectState Player::getState()
{
	return State;
}

bool Player::checkCollision(std::vector<ObjectGroupData>& objectGroupData, Rectangle body) {
	for (auto const& objectGroup : objectGroupData) {
		if (objectGroup.id == COLLISION) {
			for (auto const& object : objectGroup.objects) {
				if (CheckCollisionRecs(body, object.rectangle)) {
					return true;
				}
			}
		}
	}

	return false;
}