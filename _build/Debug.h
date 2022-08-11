#pragma once

class Game;

class Debug
{
private:
	Game* gameInstance = nullptr;
	Vector2 position;
	int fontSize = 24;
	void drawMapCollisions();
	void drawPlayerState();
	void drawPlayerInfo();
public:
	Debug(Game* gameInstance, Vector2 position);
	~Debug();
	void draw();
};

