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
		if (!checkCollision(map->objectGroupData).left) {
			if (body.x >= 0) {
				body.x -= horizontalSpeed * GetFrameTime();
			}
		}
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
		if (!checkCollision(map->objectGroupData).right) {
			if (body.x + body.width <= *map->getWidth() * map->getScale() * 16) {
				body.x += horizontalSpeed * GetFrameTime();
			}
		}
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
	//hitbox
	//DrawRectangleLinesEx(rectBottom, 2, BLACK);
	//DrawRectangleLinesEx(rectTop, 2, BLACK);
	//DrawRectangleLinesEx(rectLeft, 2, BLACK);
	//DrawRectangleLinesEx(rectRight, 2, BLACK);
}

Player::Player(Rectangle rectangle) : GameObject(rectangle) {}

void Player::update(Map* map) {
	updateMovement(map);

	if (State.isDescending) {
		move(airborne, map);
		State.isAscending = false;
		body.y += (GRAVITY / 2) * GetFrameTime();
	}

	if (checkCollision(map->objectGroupData).bottom) {
		State.isDescending = false;
		currentJumpHeight = 0;
	}
	else if (!State.isAscending) {
		State.isDescending = true;
	}

	if (checkCollision(map->objectGroupData).top) {
		currentJumpHeight = MAX_JUMP_HEIGHT;
	}

	if (State.isAscending) {
		move(airborne, map);
		if (IsKeyDown(KEY_SPACE) && currentJumpHeight < MAX_JUMP_HEIGHT) {
			body.y -= (GRAVITY / 2) * GetFrameTime();
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

Player::ObjectState Player::getState()
{
	return State;
}

Collision Player::checkCollision(std::vector<ObjectGroupData>& objectGroupData) {
	Rectangle rectTop = Rectangle{ body.x + 10.0f, body.y, body.width - 20.0f, 1.0f };
	Rectangle rectBottom = Rectangle{ body.x + 10.0f, body.y + body.height, body.width - 20.0f, 1.0f };
	Rectangle rectLeft = Rectangle{ body.x - 1.0f, body.y + 10.0f, 1.0f, body.height - 20.0f };
	Rectangle rectRight = Rectangle{ body.x + body.width + 1.0f, body.y + 10.0f, 1.0f, body.height - 20.0f };

	Collision collision = Collision {false, false, false, false };

	for (auto const& objectGroup : objectGroupData) {
		for (auto const& object : objectGroup.objects) {
			if (CheckCollisionRecs(rectTop, object.rectangle)) {
				collision.top = true;
			}
			if (CheckCollisionRecs(rectBottom, object.rectangle)) {
				collision.bottom = true;
			}
			if (CheckCollisionRecs(rectLeft, object.rectangle)) {
				collision.left = true;
			}
			if (CheckCollisionRecs(rectRight, object.rectangle)) {
				collision.right = true;
			}
		}
	}

	return collision;
}