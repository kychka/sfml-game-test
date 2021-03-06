#ifndef CIRCLEBYSEMITRO_H
#define CIRCLEBYSEMITRO_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
//Чтобы использовать класс, нужно создать его объект и передать в конструктор позицию круга в окне и радиус,
// а дальше вызвать функцию render, передав главное окно
class CircleBySemitro
{
public:
	CircleBySemitro(Vector2f position, float radius=25);
	~CircleBySemitro();
	void render(sf::RenderWindow &w);
private:
	CircleShape _circle;
};

#endif // CIRCLEBYSEMITRO_H
