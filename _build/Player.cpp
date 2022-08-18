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
		xSpeed -= 50 * GetFrameTime();
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
		xSpeed += 50 * GetFrameTime();
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
		hitBox.y++;
		if (checkCollision(map->objectGroupData, hitBox) || currentJumpHeight < MAX_JUMP_HEIGHT) {	
			ySpeed -= 50.0f * GetFrameTime();
			currentJumpHeight += 70.0f * GetFrameTime();
		}
		hitBox.y--;
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
		break;
	case IDLE:
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
	std::cout << "jumps: " << jumps << std::endl;
	std::cout << "currentJumpHeight: " << currentJumpHeight << std::endl;
	std::cout << "ySpeed: " << ySpeed << std::endl;
	updateMovement(map);

	if (ySpeed < 0) {
		State.isAscending = true;
		State.isDescending = false;
	}
	else if (ySpeed == 0) {
		if (!State.isAscending) {
			currentJumpHeight = 0;
		}
		State.isAscending = false;
		State.isDescending = false;
		if (jumps == 0) {
			jumps = 1;
		}
	}
	else if (ySpeed > 0) {
		State.isDescending = true;
		State.isAscending = false;
	}

	if (xSpeed > 0 && xSpeed < 0.75) xSpeed = 0;
	if (xSpeed < 0 && xSpeed > -0.75) xSpeed = 0;

	if (xSpeed > xMaxSpeed) xSpeed = xMaxSpeed;
	if (xSpeed < -xMaxSpeed) xSpeed = -xMaxSpeed;

	ySpeed += 15.0f * GetFrameTime();

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
		if (State.isAscending) {
			currentJumpHeight = MAX_JUMP_HEIGHT;
		}
	}

	position.x += xSpeed;
	position.y += ySpeed;

	hitBox.x = position.x;
	hitBox.y = position.y;
}

void Player::updateMovement(Map* map) {
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) || !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		// slow down gradually
		xSpeed *= 40.0f * GetFrameTime();
	}
	
	if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
		move(LEFT, map);
	}
	else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
		move(RIGHT, map);
	}
	else if (!State.isAscending) {
		move(IDLE, map);
	}

	if (IsKeyDown(KEY_SPACE) && jumps) {
		move(UP, map); 
	}
	else if (!jumps) {
		currentJumpHeight = MAX_JUMP_HEIGHT;
	}

	if (IsKeyReleased(KEY_SPACE) && jumps) {
		currentJumpHeight = 0;
		jumps--;
	}
}

Player::ObjectState Player::getState()
{
	return State;
}

bool Player::checkCollision(std::vector<ObjectGroupData>& objectGroupData, Rectangle hitBox) {
	for (auto const& objectGroup : objectGroupData) {
		if (objectGroup.id == COLLISION) {
			for (auto const& object : objectGroup.objects) {
				if (CheckCollisionRecs(hitBox, object.rectangle)) {
					return true;
				}
			}
		}
	}

	return false;
}