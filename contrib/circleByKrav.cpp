/*
	Test tasks for the team project
	Circles by KRaV
	Version 1.0
	Made by KRaV
*/
#include "circleByKrav.h"

circleByKrav::circleByKrav(sf::Vector2f coord) {
	circle_.setPosition(coord);
	circle_.setFillColor(sf::Color(121, 0, 0));
	circle_.setRadius(50);
}

sf::Shape& circleByKrav::getShape() {
	return circle_;
}
