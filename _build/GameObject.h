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
	virtual void update();
	virtual void draw();
};

