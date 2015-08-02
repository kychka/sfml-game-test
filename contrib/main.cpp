#include <SFML/Graphics.hpp>
#include "Level.h"
#include <vector>
#include <list>
#include "MapsObjects.h"
#include <iostream>
#include "tinyxml/tinyxml.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "TestExercise!");
	Level lvl;//создали экземпляр класса уровень
	lvl.LoadFromFile("Map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		lvl.Draw(window);//рисуем  карту
		window.display();
	}
	return 0;
}