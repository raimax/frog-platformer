#include "Helper.h"

float Helper::sgn(float val) {
	return (float)((0.0f < val) - (val < 0.0f));
}