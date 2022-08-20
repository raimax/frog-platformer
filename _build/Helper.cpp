#include "Helper.h"

float Helper::sgn(float val) {
	return static_cast<float>((0.0f < val) - (val < 0.0f));
}