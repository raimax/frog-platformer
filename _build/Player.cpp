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
		if (State.FacingDirection.left) {
			currentAnimation = "player_idle_left";
		}
		else {
			currentAnimation = "player_idle_right";
		}
		break;
	case airborne:
		std::cout << State.isDescending << std::endl;
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

void Player::update(GameObject* floor) {
	updateMovement();

	if (State.isDescending) {
		move(airborne);
		State.isAscending = false;
		body.y += (GRAVITY / 2) * GetFrameTime();

		if (CheckCollisionRecs(body, floor->getBody())) {
			State.isDescending = false;
			currentJumpHeight = 0;
		}
	}

	if (State.isAscending) {
		move(airborne);
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
	else if (!State.isAscending && !State.isDescending) {
		move(idle);
	};
	if (IsKeyPressed(KEY_SPACE)) {
		State.isAscending = true;
	};
}

Player::ObjectState Player::getState()
{
	return State;
}