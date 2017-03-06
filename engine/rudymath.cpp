#include "rudymath.hpp"
#include <algorithm>

float rudy::clamp(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}