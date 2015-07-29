#include<SFML\Graphics.hpp>

using namespace sf;
//класс SlonCircle
class SlonCircle{
private:
    CircleShape shape;
public:
	float x;
	float y;
	float r;
	Color shapeColor;
	SlonCircle(float X,float Y,float R);
	void draw(RenderWindow &window);
};