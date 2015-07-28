#include<SFML\Graphics.hpp>
#include<iostream>
#include<ostream>
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(1200, 800), "Circle of slon");
	CircleShape slonCircle(25.f);
	slonCircle.setFillColor(Color::Red);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){ window.close(); }
		}
		window.clear();
		window.draw(slonCircle);
		window.display();
	}

	
	return 0;
}