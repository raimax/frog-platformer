#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include <vector>
#include "Map.h"

#ifndef GRAVITY
#define GRAVITY 1000.0f
#endif // !GRAVITY

#ifndef MAX_JUMP_HEIGHT
#define MAX_JUMP_HEIGHT 300.0f
#endif // !MAX_JUMP_HEIGHT

typedef struct Collision {
	bool top;
	bool bottom;
	bool left;
	bool right;
} Collision;

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
		bool isDescending = true;
		bool isCollidingTop = false;
		bool isCollidingBottom = false;
		bool isCollidingLeft = false;
		bool isCollidingRight = false;
		struct FacingDirection {
			bool right = true;
			bool left = false;
		} FacingDirection;
	} State;
	void setFacingDirection(Direction direction);
	void move(Direction direction, Map* map);
	std::string currentAnimation = "player_fall_right";
	void updateMovement(Map* map);
	void checkCollision(std::vector<ObjectGroupData>& objectGroupData);

public:
	void draw() override;
	Player(Rectangle rectangle);
	void update(Map* map);
	ObjectState getState();
};

