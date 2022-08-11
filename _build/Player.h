#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include <vector>
#include "Map.h"

#ifndef GRAVITY
#define GRAVITY 700.0f
#endif // !GRAVITY

#ifndef MAX_JUMP_HEIGHT
#define MAX_JUMP_HEIGHT 300.0f
#endif // !MAX_JUMP_HEIGHT

enum Direction
{
	left,
	right,
	idle,
	airborne
};

class Player : public GameObject
{
private:
	float horizontalSpeed = 400.0f;
	float currentJumpHeight = 0;
	Vector2 jumpStartPosition = Vector2{-1, -1};
	struct ObjectState {
		bool isAscending = false;
		bool isDescending;
		struct FacingDirection {
			bool right;
			bool left = false;
		} FacingDirection;
	} State;
	void setFacingDirection(Direction direction);
	void move(Direction direction, Map* map);
	std::string currentAnimation = "player_fall_right";
	void updateMovement(Map* map);
	bool isCollidingBottom(std::vector<ObjectGroupData>& objectGroupData);
	bool isCollidingTop(std::vector<ObjectGroupData>& objectGroupData);
	bool isCollidingLeft(std::vector<ObjectGroupData>& objectGroupData);
	bool isCollidingRight(std::vector<ObjectGroupData>& objectGroupData);

public:
	void draw() override;
	Player(Rectangle rectangle);
	void update(Map* map);
	ObjectState getState();
};

