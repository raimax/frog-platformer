#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "AnimationManager.h"

#ifndef GRAVITY
#define GRAVITY 500.0f
#endif // !GRAVITY

#ifndef MAX_JUMP_HEIGHT
#define MAX_JUMP_HEIGHT 300.0f
#endif // !MAX_JUMP_HEIGHT

enum Direction
{
	left,
	right,
	idle,
	up
};

class Player : public GameObject
{
private:
	float horizontalSpeed = 400.0f;
	float currentJumpHeight = 0;
	Vector2 jumpStartPosition = Vector2{-1, -1};
	struct ObjectState {
		bool isAscending = false;
		bool isDescending = true;
		struct FacingDirection {
			bool right = true;
			bool left = false;
		} FacingDirection;
	} State;
	void setFacingDirection(Direction direction);
	void move(Direction direction);
	std::string currentAnimation = "player_fall_right";
	void updateMovement();

public:
	void draw() override;
	Player(Rectangle rectangle);
	void update(GameObject* floor);
	ObjectState getState();
};
