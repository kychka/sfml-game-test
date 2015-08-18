#include <SFML/Graphics.hpp>

#include "Menu\button.h"
#include "Menu\pause.h"
#include "Menu\startmenu.h"
#include "HpBar\hp_bar.h"
#include "audioManager\audioManager.hpp"
#include "level\Level.h"
#include "level\TinyXML\tinyxml.h"
#include "hero\Hero.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Scarlet!"/*, sf::Style::Fullscreen*/);	
	
	StartMenu startMenu(window);
	Pause pause(window);
	am::AudioManager mgr;

	mgr.playMusic("menu.ogg");
	startMenu.exec();

	Level lvl1;
	lvl1.LoadFromFile("resources/maps/test-map.tmx");
	std::vector<Object> mapObj;
	mapObj = lvl1.GetObjects("solid");
	
	Texture hero; ///Текстура нашего игрока 
	hero.loadFromFile("resources/images/ScarletRun2Right.png");
	Texture heroLeft;
	heroLeft.loadFromFile("resources/images/ScarletRun2Left.png");

	Animation PlayerAnim[4];
	PlayerAnim[0].setSpriteSheet(hero);
	PlayerAnim[0].loadFromXml("resources/animations/SkarletMoveRight.xml");
	PlayerAnim[1].setSpriteSheet(hero);
	PlayerAnim[1].loadFromXml("resources/animations/SkarletMoveRight.xml");
	PlayerAnim[2].setSpriteSheet(hero);
	PlayerAnim[2].loadFromXml("resources/animations/SkarletMoveRight.xml");
	PlayerAnim[3].setSpriteSheet(heroLeft);
	PlayerAnim[3].loadFromXml("resources/animations/SkarletMoveLeft.xml");

	Hero her;
	her.setHeroAnimation(PlayerAnim);
	her.setHeroPossition(0, 20);
	her.setHeroAnimationSpeed(1.0f);
	her.setHeroSpeed(20);

	sf::Clock frameClock;// Наши часики 

	float speed = 80.f;
	
	mgr.playMusic("level1.ogg");
	
	while (window.isOpen())
	{
		sf::Time frameTime = frameClock.restart();
		/*
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}*/

		window.clear();
		lvl1.Draw(window);
		her.updateAndDrawHero(frameTime, mapObj, window);
		if (Keyboard::isKeyPressed){
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				pause.exec();
		}
		window.display();
	}
	
	return 0;
}
