#pragma once
#include "raylib.h";
#include "GameObject.h"

class Animation
{
private:
	Rectangle frameRec = Rectangle{ 0, 0, 16, 16 };
	int currentFrame = 0;
	int framesCounter = 0;
	int framesSpeed = 8;
	int totalFrames = 0;
	Texture2D sprite;
	void update();
public:
	Animation(Texture2D sprite, int totalFrames, int framesSpeed = 8);
	void play(GameObject* gameObject);
};

