#include "Player.h"
#include <iostream>

void Player::setFacingDirection(Direction direction)
{
	switch (direction)
	{
	case left:
		State.FacingDirection.left = true;
		State.FacingDirection.right = false;
		break;
	case right:
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
	case left:
		body.x -= horizontalSpeed * GetFrameTime();
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
	case right:
		body.x += horizontalSpeed * GetFrameTime();
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
	case idle:
		if (State.FacingDirection.left) {
			currentAnimation = "player_idle_left";
		}
		else {
			currentAnimation = "player_idle_right";
		}
		break;
	case airborne:
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

	if (State.isDescending) {
		move(airborne, map);
		State.isAscending = false;
		body.y += (GRAVITY / 2) * GetFrameTime();
	}

	if (isColliding(map->objectGroupData)) {
		State.isDescending = false;
		currentJumpHeight = 0;
	}
	else if (!State.isAscending) {
		State.isDescending = true;
	}

	if (State.isAscending) {
		move(airborne, map);
		if (IsKeyDown(KEY_SPACE) && currentJumpHeight < MAX_JUMP_HEIGHT) {
			body.y -= GRAVITY * GetFrameTime();
			currentJumpHeight += GRAVITY * GetFrameTime();
		}
		else {
			State.isDescending = true;
		}		
	}
}

void Player::updateMovement(Map* map) {
	if (IsKeyDown(KEY_A)) {
		move(left, map);
	}
	else if (IsKeyDown(KEY_D)) {
		move(right, map);
	}
	else if (!State.isAscending && !State.isDescending) {
		move(idle, map);
	};
	if (IsKeyPressed(KEY_SPACE)) {
		State.isAscending = true;
	};
}

bool Player::isColliding(std::vector<ObjectGroupData>& objectGroupData)
{
	for (auto const& objectGroup : objectGroupData) {
		for (auto const& object : objectGroup.objects) {
			if (CheckCollisionRecs(body, object.rectangle)) {
				return true;
			}
		}
	}
	return false;
}

Player::ObjectState Player::getState()
{
	return State;
}