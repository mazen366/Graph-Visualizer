#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Boarders {
public:
	RectangleShape upper, lower;
	RectangleShape left, right;
	Boarders() {
		upper.setSize({ 1920, 10 });
		lower.setSize({ 1920, 10 });
		left.setSize({ 10, 1080 });
		right.setSize({ 10, 1080 });

		upper.setPosition({ 0,0 });
		lower.setPosition({ 0,1070 });
		left.setPosition({ 0,0 });
		right.setPosition({ 1910,0 });

		upper.setFillColor(Color::Green);
		lower.setFillColor(Color::Blue);
		left.setFillColor(Color::Red);
		right.setFillColor(Color::Yellow);
	}
	void drawBoarders(RenderWindow& window) {
		window.draw(upper);
		window.draw(lower);
		window.draw(left);
		window.draw(right);
	}
};

