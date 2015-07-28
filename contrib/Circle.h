
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class Circle
{
public:
	CircleShape shape;
	Circle(int r, int R, int G, int B, int x, int y)// r радиус круга,RGB цвет круга, x,y координаты круга
	{
		shape.setRadius(r);
		shape.setFillColor(Color(R,G,B));
		shape.setPosition(x, y);
	}
};