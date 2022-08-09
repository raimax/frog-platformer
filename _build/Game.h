#pragma once
#include "Player.h"
#include "Debug.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Map.h"
#include "MapLoader.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

class Game
{
private:
	int gameScreenWidth = 1920;
	int gameScreenHeight = 1080;
	const int windowWidth = 1280;
	const int windowHeight = 720;
	Player* player = new Player(Rectangle{ (float)gameScreenWidth / 2 - 32, (float)gameScreenHeight / 2 + 32 / 2, 64, 64 });
	GameObject* floor = new GameObject(Rectangle{ 0, (float)gameScreenHeight - 50, (float)gameScreenWidth, 50});
	Debug* debug = new Debug(this, Vector2{5, 50});
	SpriteManager* spriteManager = new SpriteManager();
	AnimationManager* animationManager = new AnimationManager();
	Map* level1;
	RenderTexture2D target;
public:
	~Game();
	void start();
	void init();
	void draw();
	void update();
	Player* getPlayer();
};

