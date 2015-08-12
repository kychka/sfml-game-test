#include "Hero\Hero.h"
#include "Hero\HpBar\hp_bar.h"
#include "AudioManager\AudioManager.hpp"
#include "Menu\button.h"
#include "Menu\pause.h"
#include "Menu\startmenu.h"

using namespace sf;
using namespace lv;
int main()
{



	
	RenderWindow window(VideoMode(1312, 400), "Skarlet");

	StartMenu startMenu(window);
	Pause pause(window);
	am::AudioManager mgr;

	mgr.playMusic("menu.ogg");
	startMenu.exec();

	lv::Level map;
	map.LoadFromFile("resources/maps/TestMap.tmx");
	std::vector<lv::Object> solidObj;
	std::vector<lv::Object> groundObj;
	solidObj = map.GetObjects("solid"); // стены итд 
	groundObj = map.GetObjects("ground"); // земля, пол 


	Texture hero; ///Текстура нашего игрока 
	hero.loadFromFile("resources/images/ScarletRun2Right.png");
	Texture heroLeft;
	heroLeft.loadFromFile("resources/images/ScarletRun2Left.png");

	Animation PlayerAnim[4];
	PlayerAnim[0].setSpriteSheet(hero);
	PlayerAnim[0].loadFromXml("resources/animations/SkarletMoveRightBeta.xml");  // Правая анимация стоя
	PlayerAnim[1].setSpriteSheet(heroLeft);
	PlayerAnim[1].loadFromXml("resources/animations/SkarletMoveLeftBeta.xml"); // Левая анимация стоя
	PlayerAnim[2].setSpriteSheet(hero);
	PlayerAnim[2].loadFromXml("resources/animations/SkarletMoveRightBeta.xml");  // Анимация в право 
	PlayerAnim[3].setSpriteSheet(heroLeft);
	PlayerAnim[3].loadFromXml("resources/animations/SkarletMoveLeftBeta.xml");  // Анимация в лево


	Hero her;
	her.setHeroAnimation(PlayerAnim);
	her.setHeroPossition(80, 500);
	her.setHeroAnimationSpeed(1.0f);
	her.setHeroSpeed(60);

	Kamera kamera(her, map, window);
	Gravi gravi(0.5);


	sf::Clock frameClock;// Наши часики 

	float speed = 80.f;

	mgr.playMusic("level1.ogg");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					
					pause.exec();
				}
				
			}
				
		}

		sf::Time frameTime = frameClock.restart();


		window.clear();
		map.Draw(window);
		her.updateAndDrawHero(frameTime, solidObj, groundObj, window);
		renderHpBar(her.getHeroHp()+50,kamera.getPossition().x+10 , kamera.getPossition().y+10, 130, 23, window, Color::Red);
		window.display();
		gravi.update(her, frameTime);
		kamera.updateKamera();
	

	}

	return 0;
}