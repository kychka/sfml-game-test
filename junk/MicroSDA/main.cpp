#include "Rectt.h"




using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1200, 800), "TeamWork");

	
	
	
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		window.display();
		
	
	}


	return 0;
}