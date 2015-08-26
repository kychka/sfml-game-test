#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy() :Enemy()
{
	setAnimationSpeed(0.6f);
}

SimpleGroundEnemy::SimpleGroundEnemy(Hero &her,Vector2f position, String name, int hp, int arm, Animation animation_mass[]) : Enemy(her,position, name, hp, arm, animation_mass)
{
	E_DX = NULL;
	E_DXL = NULL;
	E_damage = 5;
	E_HP = hp;
	E_ARM = arm;
	E_Speed = 1.0;
	E_Life = true;
	E_damage = 15;
	_onGround = true;
	setAnimationSpeed(0.6f);

}
SimpleGroundEnemy::~SimpleGroundEnemy()
{

}
void SimpleGroundEnemy::collision(std::vector<lv::Object> &allObj)
{
	Enemy::collision(allObj);
}
int SimpleGroundEnemy::getDamage()
{
	return Enemy::getDamage();
}
bool SimpleGroundEnemy::isAlive()
{
	return Enemy::isAlive();
}
void SimpleGroundEnemy::setDamage(int damage)
{
	Enemy::setDamage(damage);
} 

void SimpleGroundEnemy::collisionWithHero(){
	std::cout << "start collisionWithHero\n";
	
	if (getGlobalBounds().intersects(targetHero->getGlobalBounds())){
		std::cout << "1\n";
		if (targetHero->getDirectory() == 0){
			std::cout << "2\n";         //если игрок идет в лево
			targetHero->setHeroPossition(getPossition().x + getGlobalBounds().width, getPossition().y); std::cout << "3\n"; //отталкиваем его вправо
		}
		if (targetHero->getDirectory() == 1){
			std::cout << "4\n";         //если игрок идет вправо
			targetHero->setHeroPossition(getPossition().x - targetHero->getGlobalBounds().width, getPossition().y); std::cout << "5\n";//отталкиваем его влево
		}
		if (targetHero->getDirectory() == 4){
			std::cout << "6\n";//если игрок стоит
			if (E_DX == 0){
				std::cout << "7\n";          //если враг идет влево
				targetHero->setHeroPossition(getPossition().x - targetHero->getGlobalBounds().width, getPossition().y); std::cout << "8\n";//отталкиваем его влево
			}
			if (E_DX == 1){
				std::cout << "9\n";          //если враг идет вправо
				targetHero->setHeroPossition(getPossition().x + getGlobalBounds().width, getPossition().y); std::cout << "10\n"; //отталкиваем его вправо
			}
		}
		targetHero->setColor(Color::Red); std::cout << "11\n";
	}
}

void SimpleGroundEnemy::updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window){
	this->time = time; std::cout << "upd1\n";
	swapAnimation(); std::cout << "upd2\n";
	collisionWithHero(); std::cout << "upd3\n";
	renderHpBar(E_HP, X_Y_Poss, Vector2f(100, 20), window); std::cout << "upd4\n";
	window.draw(_Animation); std::cout << "upd5\n";
	_Animation.updateAnimation(time); std::cout << "upd6\n";
	collision(allObj); std::cout << "upd7\n";

	if (E_HP <= 0){
		std::cout << "upd8\n";
		E_Life = false; std::cout << "upd9\n";
	}
}