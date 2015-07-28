// Базовый код для рисования прямоугольников

#include "MatrixDeityRect.h"

//================================================================================

int main()
{
	system("title DEBUGGING WINDOW"); // Устанавливает заголовок окна отладки
	RenderWindow window(sf::VideoMode(1200, 800), "SFML TEST");
	
	MatrixDeityRect mdRect(Vector2f(5.0 ,695.0), Vector2f(100.0, 100.0), Color(0, 0, 255)); // Прямоугольник MatrixDeity

	while (window.isOpen())
	{
		Event myEvent;
		while (window.pollEvent(myEvent))
			if (myEvent.type == Event::Closed)
                window.close();
		window.clear();
		window.draw(mdRect.getShape());
		window.display();
	}
	return 0;
}
