#include "Rectt.h"



Rectt::Rectt(float x, float y, float w, float h, int r, int g, int b)
{
	rectangle.setPosition(x, y);
	rectangle.setSize(Vector2f(w,h));
	rectangle.setFillColor(Color (r, g, b));
	
	
}

Rectt::~Rectt()
{
}

void Rectt::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	
	
	target.draw(rectangle);
}