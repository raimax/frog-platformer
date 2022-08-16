#include "LevelScene.h"

LevelScene::LevelScene() {
	transitionStart = std::make_unique<FadeOut>();
	transitionEnd = std::make_unique<FadeIn>();
}