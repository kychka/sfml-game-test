#include "Circle.h"

circle::circle(float X, float Y, float R)
{
	x = X;
	y = Y;
	r = R;
	
	MyCircle.setPosition(X, Y);
	MyCircle.setRadius(R);
	MyCircle.setFillColor(Color(200, 50, 70));
}
void circle::CircleDraw(sf::RenderWindow &w)
{
	w.draw(MyCircle);
}
