#ifndef CAPTIONS_H
#define CAPTIONS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
// Титры
using namespace sf;
class Captions
{
public:
	Captions(RenderWindow &window);
	~Captions();
	void show();
private:
	Font _font;
	Text* _text;
	Music _music;
	RenderWindow &_w;
};

#endif // CAPTIONS_H
