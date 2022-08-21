#include "Helper.h"

float Helper::sgn(float val) {
	return static_cast<float>((0.0f < val) - (val < 0.0f));
}

Rectangle Helper::getRecCenter(Rectangle rectangle) {
	return Rectangle{ rectangle.x + rectangle.width / 4, rectangle.y + rectangle.height / 4, rectangle.width, rectangle.height };
}