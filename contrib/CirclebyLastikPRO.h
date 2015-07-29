
#include <SFML/Graphics.hpp>
using namespace sf;

class circle
{
public:
	CircleShape shape;
	circle( int x, int y);
	void render(RenderWindow &window);
};
