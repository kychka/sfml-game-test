#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class circle
{
	public:
		float x, y, r;
		Texture texture;
		CircleShape MyCircle;
		circle(float X, float Y,  float R);
		void CircleDraw(sf::RenderWindow &w);
};
