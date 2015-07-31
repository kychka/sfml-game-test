#include "enteyCircle.h"

Circle::Circle() { 
		x = 0; 
		y = 0; 
		size = 100.f; 
		color = "white";
	}

Circle::Circle(char *c, int s, int X, int Y){
	int l = strlen(c);
	color = new char[l];
	strcpy(color,c);
	size = s;
	x = X;
	y = Y;
	}

sf::CircleShape Circle::view(){
		
		sf::CircleShape shape(size);
		shape.setPosition(x,y);
		
		if(strstr(color,"yellow"))
			choice = 1;
		if(strstr(color,"blue"))
			choice = 2;
		if(strstr(color,"red"))
			choice = 3;
		if(strstr(color,"green"))
			choice = 4;

		switch(choice){
		case 1: shape.setFillColor(sf::Color::Yellow); break;
		case 2: shape.setFillColor(sf::Color::Blue); break;
		case 3: shape.setFillColor(sf::Color::Red); break;
		case 4: shape.setFillColor(sf::Color::Green); break;
		default: shape.setFillColor(sf::Color::White); break;
		}
		return shape;
	}
