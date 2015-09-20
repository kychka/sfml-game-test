#include "Hero/Hero.h"
#include "Hero/HpBar/hp_bar.h"
#include "AudioManager/AudioManager.hpp"
#include "Menu/button.h"
#include "Menu/pause.h"
#include "Menu/startmenu.h"
#include "Hero/simplegroundenemy.h"
#include "Hero/Weapons.h"

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

	std::cout << "1\n";
	Hero her; std::cout << "2\n";
	her.setHeroAnimation(PlayerAnim);
	her.setHeroPossition(80, 500);
	her.setHeroAnimationSpeed(0.6f);
	her.setHeroSpeed(80);
	her.setHeroJump(6.5);
	her.setGraviForHero(3.3);
	Kamera kamera(her, map, window);

	/*std::vector<SimpleGroundEnemy*> enemies;
	std::vector<SimpleGroundEnemy*>::iterator it;*/

	/*enemies.push_back(new SimpleGroundEnemy(her, Vector2f(500, 500), "SimpleGroundEnemy", 50, 50, PlayerAnim));*/


    Texture SimpleGroundEnemyShootLeft;//Текстура врага для стрельбы
	SimpleGroundEnemyShootLeft.loadFromFile("resources/images/RobotShootingLeft.png");

	Texture SimpleGroundEnemyShootRight;
	SimpleGroundEnemyShootRight.loadFromFile("resources/images/RobotShootingRight.png");
	
	Texture SimpleSimpleGroundEnemyWalkLeft;
	SimpleSimpleGroundEnemyWalkLeft.loadFromFile("resources/images/RobotWalkLeft.png");
	Texture	SimpleSimpleGroundEnemyWalkRight;
	SimpleSimpleGroundEnemyWalkRight.loadFromFile("resources/images/RobotWalkRight.png");

	//Анимация стрельбы врага
    Animation EnemyAnimation[4];
	
	EnemyAnimation[0].setSpriteSheet(SimpleGroundEnemyShootRight);
    EnemyAnimation[0].loadFromXml("resources/animations/RobotShootingRight.xml");

	EnemyAnimation[1].setSpriteSheet(SimpleGroundEnemyShootLeft); //Анимация стрельбы врага
	EnemyAnimation[1].loadFromXml("resources/animations/RobotShootingLeft.xml");

	EnemyAnimation[2].setSpriteSheet(SimpleSimpleGroundEnemyWalkLeft); //Анимация бега врага
	EnemyAnimation[2].loadFromXml("resources/animations/RobotWalkLeft.xml");

	EnemyAnimation[3].setSpriteSheet(SimpleSimpleGroundEnemyWalkRight); //Анимация бега врага
	EnemyAnimation[3].loadFromXml("resources/animations/RobotWalkRigth.xml");



   // SimpleGroundEnemy enm(her, kamera, Vector2f(1400, 600), "SimpleGroundEnemy", 50, 50, EnemyAnimation);
  //  enm.setAnimationSpeed(0.6f);

	std::list<SimpleGroundEnemy*> EnemyMass;
	std::list<SimpleGroundEnemy*>::iterator EnemyMassIT;

	EnemyMass.push_back(new SimpleGroundEnemy(her, kamera, Vector2f(1400, 300), "SimpleGroundEnemy", 100, 50, EnemyAnimation));



	Clock clock;// Наши часики 
	Time time;
	float frametime = NULL;

	Weapon weaponHero;
	Texture weapon_texture;
	weapon_texture.loadFromFile("resources/images/bullet.png");
	weaponHero.inicialize(weapon_texture, 100, 1, her);
	
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
		//map.Draw(window);	// tiny
		window.draw(map);	// pugi
		for (EnemyMassIT = EnemyMass.begin(); EnemyMassIT != EnemyMass.end(); EnemyMassIT++){
			(*EnemyMassIT)->updateAndDraw(time, allObj, window);
			if (!(*EnemyMassIT)->isAlive()){ EnemyMass.remove((*EnemyMassIT)); break; }
		}
		//enm.updateAndDraw(time, allObj, window);
		her.updateAndDrawHero(frametime, time, solidObj, groundObj , window);
		renderHpBar(her.getHeroHp(), kamera.getPossition().x + 10, kamera.getPossition().y + 10, 130, 23, window, Color::Red);
		renderHpBar(weaponHero.getAmmoSize(), kamera.getPossition().x + 10, kamera.getPossition().y + 50, 130, 23, window, Color::Blue);/// Бар колв патронов 
		weaponHero.update(window, kamera, solidObj, frametime, her, EnemyMass);
		window.display();
		kamera.updateKamera();


	}

	return 0;
}
