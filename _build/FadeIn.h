#pragma once
#include "Transition.h"
#include "raylib.h"

class FadeIn : public Transition
{
private:
	float opacity = 255;
public:
	void play() override;
};

