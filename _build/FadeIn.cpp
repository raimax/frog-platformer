#include "FadeIn.h"

void FadeIn::play()
{
	if (!transitionEnded) {
		opacity -= opacity * GetFrameTime() * 2.0f;
		if (opacity < 1) {
			opacity = 0;
			transitionEnded = true;
		}
		DrawRectangle(0, 0, 1920, 1080, Color{ 0, 0, 0, (unsigned char)opacity });
	}
}


