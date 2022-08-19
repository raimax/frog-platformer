#pragma once
#include "raylib.h"

class GameObject
{
protected:
	Rectangle hitBox;
	Vector2 position;
public:
	~GameObject();
	GameObject(Rectangle body);
	Rectangle* getHitBox();
	Vector2* getPosition();
	virtual void update();
	virtual void draw();
};

