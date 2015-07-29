#include<SFML/Graphics.hpp>
#include"CirclebyLastikPRO.h"

using namespace sf;

circle::circle( int x, int y)
{
	shape.setFillColor(Color(128, 21, 46));
	shape.setRadius(100);
	shape.setPosition(x, y);
}
void circle::render(RenderWindow &window)
{
	window.draw(shape);
}