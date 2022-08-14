#pragma once
#include "Player.h"
#include "Debug.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Map.h"
#include "MapLoader.h"
#include "SceneManager.h"
#include "TransitionManager.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

class Game
{
private:
	const int GAME_SCREEN_WIDTH = 1920;
	const int GAME_SCREEN_HEIGHT = 1080;
	const int windowWidth = 1280;
	const int windowHeight = 720;
	bool debugEnabled = false;
	std::unique_ptr<Debug> debug = std::make_unique<Debug>(this, Vector2{ 5, 50 });
	std::unique_ptr<SpriteManager> spriteManager = std::make_unique<SpriteManager>();
	std::unique_ptr<AnimationManager> animationManager = std::make_unique<AnimationManager>();
	RenderTexture2D target;
public:
	std::unique_ptr<SceneManager> sceneManager = std::make_unique<SceneManager>();
	static Font font;
	static bool exitWindow;
	~Game();
	void start();
	void init();
	void draw();
	void update();
	void toggleDebug();
	Player* getPlayer();
};

