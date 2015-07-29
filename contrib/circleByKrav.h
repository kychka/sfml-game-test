/*
	Test tasks for the team project
	Circles by KRaV
	Version 1.0
	Made By KRaV
*/
#ifndef CIRCLEBYKRAV_H
#define CIRCLEBYKRAV_H

#include <SFML\Graphics.hpp>

/*
	Class circleByKrav.

	Using:
	- for create a object, use the constructor (see below).
	- for get object use getShape() function.
*/

class circleByKrav {
public:
	circleByKrav(sf::Vector2f coord);	// class constructor, parameters - coordinates of circle
	sf::Shape& getShape();				// function returning a reference to circle_ object
protected:
	sf::CircleShape circle_;			// circle object
};

#endif
