#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Rectt : public sf::Drawable, public sf::Transformable// Унаследовал ( для простой отрисовки)
{
public:
	Rectt();
	Rectt(float x, float y, float w, float h, int r, int g, int b); // позиция, размер, и цвет.
	~Rectt();
private:
	RectangleShape rectangle; // Наш ректангл
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

