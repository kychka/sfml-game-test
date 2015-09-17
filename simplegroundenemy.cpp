#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy(Hero &Her, Kamera &kam) :Enemy(Her,kam)
{
	setAnimationSpeed(0.6f);
	distance = 2000;
}

SimpleGroundEnemy::SimpleGroundEnemy(Hero &her, Kamera &kam, Vector2f position, String name, int hp, int arm, Animation animation_mass[]) : Enemy(her, kam, position, name, hp, arm, animation_mass)
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
	distance = 2000;

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
			if (getGlobalBounds().left>targetHero.getGlobalBounds().left){
				          //если игрок левее
				targetHero.setHeroPossition(getPossition().x - targetHero.getGlobalBounds().width, targetHero.getHeroPossition().y);//отталкиваем его влево
			}
			if (getGlobalBounds().left<targetHero.getGlobalBounds().left){
				          //если игрок правее
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
	seeTarget(allObj,window);
	renderHpBar(E_HP, X_Y_Poss, Vector2f(100, 20), window);
	window.draw(_Animation); 
	_Animation.updateAnimation(time);
	collision(allObj); 

	if (E_HP <= 0){
		E_Life = false;
	}
}



bool SimpleGroundEnemy::seeTarget(std::vector<lv::Object> &allObj, RenderWindow &window){//видит ли враг игрока

	if (kamera.getVisebleZone().intersects(targetHero.getGlobalBounds())){
		if ((getGlobalBounds().top > targetHero.getGlobalBounds().top + targetHero.getGlobalBounds().height) || (getGlobalBounds().top + getGlobalBounds().height < targetHero.getGlobalBounds().top)){
			//если игрок выше или ниже врага
			return false;
		}
		
			if (getGlobalBounds().left < targetHero.getGlobalBounds().left){//если игрок правее врага
				for (int i = 0; i < allObj.size(); i++){//пробегаемся по вектору обьектов
					if (allObj[i].name == "solid"){//если имя обьекта solid
						if ((getGlobalBounds().left < allObj[i].rect.left) && (allObj[i].rect.left < targetHero.getGlobalBounds().left)){//есть ли между врагом и игроком обьект солид то..
							if (!((getGlobalBounds().top < allObj[i].rect.top) && (targetHero.getGlobalBounds().top < allObj[i].rect.top))){//..проверяем может ли враг заглянуть через него сверху
								if (!((getGlobalBounds().top + getGlobalBounds().height / 2>allObj[i].rect.top + allObj[i].rect.height) && (allObj[i].rect.top + allObj[i].rect.height < targetHero.getGlobalBounds().top + targetHero.getGlobalBounds().height)))
									//может ли враг заглянуть под обьект
									return false;
							}
						}
					}
				}
				_Animation.setColor(Color::Green);
				return true;
			}
			if (getGlobalBounds().left > targetHero.getGlobalBounds().left){//если игрок левее
				for (int i = 0; i < allObj.size(); i++){
					if (allObj[i].name == "solid"){
						if ((getGlobalBounds().left > allObj[i].rect.left) && (allObj[i].rect.left > targetHero.getGlobalBounds().left)){
							if (!((getGlobalBounds().top < allObj[i].rect.top) && targetHero.getGlobalBounds().top<allObj[i].rect.top))
								if (!((getGlobalBounds().top + getGlobalBounds().height / 2>allObj[i].rect.top + allObj[i].rect.height) && (allObj[i].rect.top + allObj[i].rect.height < targetHero.getGlobalBounds().top + targetHero.getGlobalBounds().height)))
									return false;
						}
					}
				}
				_Animation.setColor(Color::Green);
				return true;
			}
		}		
}
