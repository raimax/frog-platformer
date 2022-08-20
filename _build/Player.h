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
	const float MAX_JUMP_HEIGHT = 15.0f;
	const float MOVE_SPEED = 8.0f;
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
	void move(float x, float y, Map* map);
	void checkX(float x, Map* map);
	void checkY(float y, Map* map);
	std::string currentAnimation = "player_fall_right";
	void updateMovement(Map* map);
	Rectangle checkCollision(std::vector<ObjectGroupData>& objectGroupData, Rectangle hitBox);
	void updateCollisionDirections(float x, float y);
	void resetCollisionDirections();
public:
	void draw() override;
	Player(Rectangle rectangle);
	void update(Map* map);
	ObjectState getState();
};

