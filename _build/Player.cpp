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

void Player::move(Direction direction)
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
		if (State.isAscending || State.isDescending) break;

		if (State.FacingDirection.left) {
			currentAnimation = "player_idle_left";
		}
		else {
			currentAnimation = "player_idle_right";
		}
		break;
	case up:
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
	default:
		break;
	}
}

void Player::draw() {
	AnimationManager::playAnimation(currentAnimation, this);
}

Player::Player(Rectangle rectangle) : GameObject(rectangle) {}

void Player::update(GameObject* floor) {
	updateMovement();

	if (State.isDescending) {
		State.isAscending = false;
		body.y += (GRAVITY / 2) * GetFrameTime();

		if (CheckCollisionRecs(body, floor->getBody())) {
			State.isDescending = false;
			currentJumpHeight = 0;
		}
	}

	if (State.isAscending) {
		if (IsKeyDown(KEY_SPACE) && currentJumpHeight < MAX_JUMP_HEIGHT) {
			body.y -= GRAVITY * GetFrameTime();
			currentJumpHeight += GRAVITY * GetFrameTime();
		}
		else {
			State.isDescending = true;
		}		
	}
}

void Player::updateMovement() {
	if (IsKeyDown(KEY_A)) {
		move(left);
	}
	else if (IsKeyDown(KEY_D)) {
		move(right);
	}
	else {
		move(idle);
	};
	if (IsKeyPressed(KEY_SPACE) && !State.isDescending) {
		State.isAscending = true;
		move(up);
	};
}

Player::ObjectState Player::getState()
{
	return State;
}