#include <SFML/Graphics.hpp>
#include "enteyCircle.h"
 
int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Entey");

	Circle ob1;
	Circle ob2("yellow",200.f,0,0);
	Circle ob3("red",100.f,200,0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
 
		window.clear();
		window.draw(ob2.view());
		window.draw(ob3.view());
		window.draw(ob1.view());
		window.display();
	}
 
	return 0;
}
