#pragma once
#include "Player.h"
#include "Debug.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Map.h"
#include "MapLoader.h"

#define SCREEN_W 1280
#define SCREEN_H 720

class Game
{
private:
	Player* player = new Player(Rectangle{ SCREEN_W / 2 - 32, SCREEN_H / 2 + 32 / 2, 64, 64});
	GameObject* floor = new GameObject(Rectangle{0, SCREEN_H - 50, SCREEN_W, 50});
	Debug* debug = new Debug(this, Vector2{5, 50});
	SpriteManager* spriteManager = new SpriteManager();
	AnimationManager* animationManager = new AnimationManager();
	Map* level1;
public:
	~Game();
	void start();
	void init();
	void draw();
	void update();
	Player* getPlayer();
};

