#include "button.h"

Button::Button(String text, Vector2f position, unsigned int character_size)
{
	_font.loadFromFile("resources/fonts/font.ttf");
	_text = Text(text,_font,character_size);
	_text.setPosition(position);
	_focus = false;
}
Button::Button(String text, float position_x, float position_y, unsigned int character_size){
	_font.loadFromFile("resources/fonts/font.ttf");
	_text = Text(text,_font,character_size);
	_text.setPosition(Vector2f(position_x,position_y));
	_focus = false;
}
Button::~Button()
{

}
void Button::render(RenderWindow &window){
	if(_focus)
		_text.setColor(Color(10,110,10));
	else
		_text.setColor(Color(Color::White));
	window.draw(_text);
}
void Button::setFocus(bool focus){
	_focus = focus;
}

FloatRect Button::getGlobalBounds(){
	return _text.getGlobalBounds();
}
