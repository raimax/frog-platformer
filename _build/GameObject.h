#pragma once
#include "raylib.h"

class GameObject
{
protected:
	Rectangle body;
public:
	~GameObject();
	GameObject(Rectangle body);
	Rectangle getBody();
	void update();
	virtual void draw();
};

