#pragma once

class Game;

class Debug
{
private:
	Game* gameInstance = nullptr;
	Vector2 position;
	float fontSize = 24.0f;
	void drawMapCollisions();
	void drawPlayerState();
	void drawPlayerInfo();
public:
	Debug(Game* gameInstance, Vector2 position);
	~Debug();
	void draw();
};

