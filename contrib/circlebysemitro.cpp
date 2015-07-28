#include "circlebysemitro.h"

CircleBySemitro::CircleBySemitro(Vector2f position, float radius)
{
	_circle.setRadius(radius);
	_circle.setPosition(position);
	_circle.setFillColor(Color(200,50,72));
}

CircleBySemitro::~CircleBySemitro()
{

}

void CircleBySemitro::render(RenderWindow &w){
	w.draw(_circle);
}
