#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;
// Используется в классе pause
class Button
{
public:
	Button(String text,Vector2f position,unsigned int character_size=30);
	Button(String text,float position_x, float position_y, unsigned int character_size=30);
	FloatRect getGlobalBounds();
	~Button();
	void render(RenderWindow &window);
	void setFocus(bool focus = true);
private:
	Text _text;
	Font _font;
	bool _focus; // Выделять ли кнопку?
};

#endif // BUTTON_H
