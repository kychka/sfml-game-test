
#include <SFML/Graphics.hpp>
#include "Circle.h"
using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(1200, 800), "SFML");
	Circle circle(100, 237, 18, 62, 300, 1);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(circle.shape);
		window.display();
	}

	return 0;
}