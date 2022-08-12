#pragma once
#include "Player.h"
#include "Debug.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Map.h"
#include "MapLoader.h"
#include "SceneManager.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

class Game
{
private:
	int gameScreenWidth = 1920;
	int gameScreenHeight = 1080;
	const int windowWidth = 1280;
	const int windowHeight = 720;
	bool debugEnabled = false;
	Debug* debug = new Debug(this, Vector2{5, 50});
	SpriteManager* spriteManager = new SpriteManager();
	AnimationManager* animationManager = new AnimationManager();
	RenderTexture2D target;
public:
	std::unique_ptr<SceneManager> sceneManager = std::make_unique<SceneManager>();
	Font font;
	~Game();
	void start();
	void init();
	void draw();
	void update();
	void toggleDebug();
	Player* getPlayer();
};

