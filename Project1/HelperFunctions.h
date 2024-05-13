#pragma once
#include "SFMLNode.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class helperFunctions
{
public:
	float static randomFloat(float min, float max);
	double static getDistance(int x1, int y1, int x2, int y2);

};

