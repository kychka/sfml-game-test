#include "Rectt.h"




using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1200, 800), "TeamWork");

	Rectt rectc4(740, 540, 50, 50, 125, 215, 130);
	Rectt rectc2(630, 500, 50, 50, 100, 200, 0);
	Rectt rectc3(530, 330,50, 50, 0, 255 ,100);
	
	

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