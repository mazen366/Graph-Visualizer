#include "helperFunctions.h"
#include "SFMLNode.h"
float helperFunctions::randomFloat(float min, float max) {
	int randomInt = rand();
	float randomFraction = static_cast<float>(randomInt) / RAND_MAX;
	return min + randomFraction * (max - min);
}
double helperFunctions::getDistance(int x1, int y1, int x2, int y2)
{
	return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}