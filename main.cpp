#include "Hero\Hero.h"
#include "Hero\HpBar\hp_bar.h"
#include "AudioManager\AudioManager.hpp"
#include "Menu\button.h"
#include "Menu\pause.h"
#include "Menu\startmenu.h"
#include "Hero\simplegroundenemy.h"
#include <iostream>

using namespace sf;
using namespace lv;

int main()
{
	RenderWindow window(VideoMode(1312, 800), "Skarlet"); /// Без тулбара, можно поменять 

	StartMenu startMenu(window);
	Pause pause(window);
	am::AudioManager mgr;

	mgr.playMusic("menu.ogg");
	startMenu.exec();

	lv::Level map;
	map.LoadFromFile("resources/maps/TestMap.tmx");
	std::vector<lv::Object> solidObj;
	std::vector<lv::Object> groundObj;
	std::vector<lv::Object> allObj;
	solidObj = map.GetObjects("solid"); // стены итд 
	groundObj = map.GetObjects("ground"); // земля, пол 
	allObj = map.GetAllObjects();


	Texture SimpleGroundEnemyRun; //Текстура врага для бега
	SimpleGroundEnemyRun.loadFromFile("resources/images/RobotWalk.png");

	Texture SimpleGroundEnemyShoot;//Текстура врага для стрельбы
	SimpleGroundEnemyShoot.loadFromFile("resources/images/RobotShooting.png");

	Animation EnemyAnimation[2];

	EnemyAnimation[0].setSpriteSheet(SimpleGroundEnemyRun); //Анимация бега врага
	EnemyAnimation[0].loadFromXml("resources/animations/RobotWalk.xml");

	EnemyAnimation[1].setSpriteSheet(SimpleGroundEnemyShoot); //Анимация стрельбы врага
	EnemyAnimation[1].loadFromXml("resources/animations/RobotShooting.xml");


	Texture heroRight; ///Текстура нашего игрока 
	heroRight.loadFromFile("resources/images/TanyaRunRight.png");

	Texture heroLeft;
	heroLeft.loadFromFile("resources/images/TanyaRunLeft.png");

	Texture heroFireLeft;
	heroFireLeft.loadFromFile("resources/images/TanyaRunShotLeft.png");

	Texture heroFireRight;
	heroFireRight.loadFromFile("resources/images/TanyaRunShotRight.png");

	Texture heroFireRunRight;
	heroFireRunRight.loadFromFile("resources/images/TanyaRunShotRight.png");

	Texture heroFireRunLeft;
	heroFireRunLeft.loadFromFile("resources/images/TanyaRunShotLeft.png");

	Animation PlayerAnim[8];
	PlayerAnim[0].setSpriteSheet(heroRight);
	PlayerAnim[0].loadFromXml("resources/animations/TanyRunRight.xml");  // Правая анимация стоя
	PlayerAnim[1].setSpriteSheet(heroLeft);
	PlayerAnim[1].loadFromXml("resources/animations/TanyRunLeft.xml"); // Левая анимация стоя
	PlayerAnim[2].setSpriteSheet(heroRight);
	PlayerAnim[2].loadFromXml("resources/animations/TanyRunRight.xml");  // Анимация бег в право 
	PlayerAnim[3].setSpriteSheet(heroLeft);
	PlayerAnim[3].loadFromXml("resources/animations/TanyRunLeft.xml");  // Анимация бег в лево

	PlayerAnim[4].setSpriteSheet(heroFireRunRight);
	PlayerAnim[4].loadFromXml("resources/animations/TanyaRunFireRight.xml"); // Стрельа на ходу право

	PlayerAnim[5].setSpriteSheet(heroFireRunLeft);
	PlayerAnim[5].loadFromXml("resources/animations/TanyaRunFireLeft.xml"); // Стрельба на ходу лево

	PlayerAnim[6].setSpriteSheet(heroFireLeft);
	PlayerAnim[6].loadFromXml("resources/animations/TanyaRunFireLeft.xml");//Стрельба стоя лево

	PlayerAnim[7].setSpriteSheet(heroFireRight);
	PlayerAnim[7].loadFromXml("resources/animations/TanyaRunFireRight.xml");//Стрельба стоя право 


	Hero her;
	her.setHeroAnimation(PlayerAnim);
	her.setHeroPossition(80, 500);
	her.setHeroAnimationSpeed(0.6f);
	her.setHeroSpeed(80);
	her.setHeroJump(6.5);
	her.setGraviForHero(3.3);
	Vector2f enmPosition(380, 570);
	SimpleGroundEnemy enm(enmPosition, "Enemy", 50, 50, EnemyAnimation);
	enm.setAnimationSpeed(1.1f);

	Kamera kamera(her, map, window);

	Clock clock;// Наши часики 
	Time time;
	float frametime = NULL;

	mgr.playMusic("level1.ogg");

	while (window.isOpen())
	{

		frametime = clock.getElapsedTime().asMilliseconds();
		time = clock.getElapsedTime();
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
				pause.exec();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					pause.exec();
				}

			}

		}



		window.clear();
		map.Draw(window);
		her.updateAndDrawHero(frametime, time, solidObj, groundObj, window);
		enm.updateAndDraw(time, allObj, window);
		renderHpBar(her.getHeroHp() + 50, kamera.getPossition().x + 10, kamera.getPossition().y + 10, 130, 23, window, Color::Red);
		window.display();
		kamera.updateKamera();


	}

	return 0;
}