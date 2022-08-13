#include "FadeOut.h"

void FadeOut::play()
{
	if (!transitionEnded) {
		opacity += opacity * GetFrameTime() * 8.0f;
		if (opacity >= 255) {
			opacity = 255;
			transitionEnded = true;
		}
		DrawRectangle(0, 0, 1920, 1080, Color{ 0, 0, 0, (unsigned char)opacity });
	}
}
