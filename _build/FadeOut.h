#pragma once
#include "Transition.h"
#include "raylib.h"

class FadeOut : public Transition
{
private:
	float opacity = 1;
public:
	void play() override;
};

