#include "captions.h"

Captions::Captions(RenderWindow &window) : _w(window)
{
	_font.loadFromFile("resources/fonts/font.ttf");
	String a;
	a = L"Создатели\nБуква Й\nГорен Степаныч\nНужен список девелоперов)";
	_text = new Text(a,_font);
	_text->setPosition(_w.getView().getSize().x/2.5,_w.getView().getSize().y-15);
}

Captions::~Captions()
{
	delete _text;
}

void Captions::show(){
	Event event;
	sf::Clock clock;
	while(true){
		clock.restart();
		while(_w.pollEvent(event))
			if(event.type == Event::Closed
					||
			   (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
				return;
		_w.clear();
		_w.draw(*_text);
		_w.display();
		_text->move(0,-clock.getElapsedTime().asMicroseconds()/10000);
	}
}
