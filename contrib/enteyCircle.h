#pragma once
#include <SFML\Graphics.hpp>

class Circle {
	char *color;
	int choice;
	float size;
	int x,y;
public:
	Circle();
	Circle(char *c, int s, int X, int Y);
	sf::CircleShape view();	
};
