#include "Hero.h"


using namespace sf;
using namespace lv;
int main()
{

	RenderWindow window(VideoMode(1200, 800), "sds");
	Level lv;
	lv.LoadFromFile("Test map.tmx");
	std::vector<Object> mapObj;
	
	mapObj = lv.GetObjects("solid");
	//Event event;


	Texture hero; ///Текстура нашего игрока 
	hero.loadFromFile("ScarletRun2Right.png");
	Texture heroLeft;
	heroLeft.loadFromFile("ScarletRun2Left.png");

	Animation PlayerAnim[4];
	PlayerAnim[0].setSpriteSheet(hero);
	PlayerAnim[0].loadFromXml("SkarletMoveRight.xml");
	PlayerAnim[1].setSpriteSheet(hero);
	PlayerAnim[1].loadFromXml("SkarletMoveRight.xml");
	PlayerAnim[2].setSpriteSheet(hero);
	PlayerAnim[2].loadFromXml("SkarletMoveRight.xml");
	PlayerAnim[3].setSpriteSheet(heroLeft);
	PlayerAnim[3].loadFromXml("SkarletMoveLeft.xml");


	Hero her;
	her.setHeroAnimation(PlayerAnim);
	her.setHeroPossition(0, 20);
	her.setHeroAnimationSpeed(1.0f);
	her.setHeroSpeed(20);

	sf::Clock frameClock;// Наши часики 

	float speed = 80.f;
	
	
	while (window.isOpen())
	{

		sf::Time frameTime = frameClock.restart();
		

			window.clear();
			lv.Draw(window);
			her.updateAndDrawHero(frameTime, mapObj, window);
			window.display();
			
		}

	
	
	return 0;
}