#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy(Hero &Her) :Enemy(Her)
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
	
	
	if (getGlobalBounds().intersects(targetHero.getGlobalBounds())){
		
		if (targetHero.getDirectory() == 0){         //если игрок идет в лево
			targetHero.setHeroPossition(getPossition().x + getGlobalBounds().width, targetHero.getHeroPossition().y); //отталкиваем его вправо
		}
		if (targetHero.getDirectory() == 1){
			        //если игрок идет вправо
			targetHero.setHeroPossition(getPossition().x - targetHero.getGlobalBounds().width, targetHero.getHeroPossition().y);//отталкиваем его влево
		}
		if (targetHero.getDirectory() == 4){
			//если игрок стоит
			if (E_DX == 0){
				          //если враг идет влево
				targetHero.setHeroPossition(getPossition().x - targetHero.getGlobalBounds().width, targetHero.getHeroPossition().y);//отталкиваем его влево
			}
			if (E_DX == 1){
				          //если враг идет вправо
				targetHero.setHeroPossition(getPossition().x + getGlobalBounds().width, targetHero.getHeroPossition().y); //отталкиваем его вправо
			}
		}
		targetHero.takeDamage(getDamage());//игрок получает урон
	}
}

void SimpleGroundEnemy::updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window){
	this->time = time; 
	swapAnimation(); 
	collisionWithHero(); 
	renderHpBar(E_HP, X_Y_Poss, Vector2f(100, 20), window);
	window.draw(_Animation); 
	_Animation.updateAnimation(time);
	collision(allObj); 

	if (E_HP <= 0){
		E_Life = false;
	}
}