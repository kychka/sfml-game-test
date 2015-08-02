#include "button.h"

Button::Button(String text, Vector2f position, unsigned int character_size)
{
	_font.loadFromFile("Fonts/font.ttf");
	_text = Text(text,_font,character_size);
	_text.setPosition(position);
}
Button::Button(String text, float position_x, float position_y, unsigned int character_size){
	_font.loadFromFile("Fonts/font.ttf");
	_text = Text(text,_font,character_size);
	_text.setPosition(Vector2f(position_x,position_y));
}
Button::~Button()
{

}
void Button::render(RenderWindow &window, bool has_focus){
	if(has_focus == true)
		_text.setColor(Color(10,110,10));
	else
		_text.setColor(Color(Color::White));
	window.draw(_text);
}
