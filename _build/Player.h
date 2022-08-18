#pragma once
#include "raylib.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include <vector>
#include "Map.h"
#include "Helper.h"

enum Direction
{
	LEFT,
	RIGHT,
	IDLE,
	UP,
};

class Player : public GameObject
{
private:
	float xSpeed = 0;
	float ySpeed = 0;
	float xMaxSpeed = 7;
	const float MAX_JUMP_HEIGHT = 20.0f;
	float currentJumpHeight = 0;
	bool doubleJump = true;
	int jumps = 2;
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
	bool checkCollision(std::vector<ObjectGroupData>& objectGroupData, Rectangle hitBox);

public:
	void draw() override;
	Player(Rectangle rectangle);
	void update(Map* map);
	ObjectState getState();
};

