#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy(Hero &Her) :Enemy(Her)
{
	setAnimationSpeed(0.6f);
	distance = 2000;
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
	/*if (targetHero.getGlobalBounds().left>getGlobalBounds().left){*/
	FloatRect visebleZoneRight(getGlobalBounds().left + getGlobalBounds().width, getGlobalBounds().top, distance, 53);//проверка пространства справа от врага
	FloatRect visebleZoneLeft(getGlobalBounds().left ,getGlobalBounds().top,-distance,53);
	if (targetHero.getGlobalBounds().left > getGlobalBounds().left + getGlobalBounds().width){
		for (int i = 0; i < allObj.size(); i++){
			if (allObj[i].name == "solid"){
				if (allObj[i].rect.intersects(visebleZoneRight)){
					if (allObj[i].rect.top > visebleZoneRight.top){
						visebleZoneRight.height = allObj[i].rect.top - visebleZoneRight.top;
					}
					if (allObj[i].rect.top + allObj[i].rect.height < visebleZoneRight.top + visebleZoneRight.height){
						int x=visebleZoneRight.top = (visebleZoneRight.top + visebleZoneRight.height) - (allObj[i].rect.top + allObj[i].rect.height);
						visebleZoneRight.height = visebleZoneRight.height - x;
					}
					if ((allObj[i].rect.top<visebleZoneRight.top)&&(allObj[i].rect.top + allObj[i].rect.height>visebleZoneRight.top+visebleZoneRight.height)){
						visebleZoneRight.width = allObj[i].rect.left - (getGlobalBounds().left + getGlobalBounds().width);
				}
			}
		}
			
	}
		if (visebleZoneRight.intersects(targetHero.getGlobalBounds())){
			_Animation.setColor(Color::Green);
			return true;
		}
		else{
			return false;
		}

	}
	if ((targetHero.getGlobalBounds().left + targetHero.getGlobalBounds().width) < getGlobalBounds().left){
		for (int i = 0; i < allObj.size(); i++){
			if (allObj[i].name == "solid"){
				if (allObj[i].rect.intersects(visebleZoneLeft)){
					if (allObj[i].rect.top > visebleZoneLeft.top){
						visebleZoneLeft.height = allObj[i].rect.top - visebleZoneLeft.top;
					}
					if (allObj[i].rect.top + allObj[i].rect.height < visebleZoneLeft.top + visebleZoneLeft.height){
						int x = visebleZoneLeft.top = (visebleZoneLeft.top + visebleZoneLeft.height) - (allObj[i].rect.top + allObj[i].rect.height);
						visebleZoneLeft.height = visebleZoneRight.height - x;
					}
					if ((allObj[i].rect.top<visebleZoneLeft.top) && (allObj[i].rect.top + allObj[i].rect.height>visebleZoneLeft.top + visebleZoneLeft.height)){
						visebleZoneLeft.width = getGlobalBounds().left - (allObj[i].rect.left + allObj[i].rect.width);
						visebleZoneLeft.left = getGlobalBounds().left - visebleZoneLeft.width;
						
					}
				}
			}
		}

		if (visebleZoneLeft.intersects(targetHero.getGlobalBounds())){
			_Animation.setColor(Color::Green);
			return true;
		}
		else{
			return false;
		}

	}
		
	
		/*RectangleShape rec(Vector2f(visebleZone.top,visebleZone.left));
		rec.setSize(Vector2f(visebleZone.width,visebleZone.height ));
		rec.setFillColor(Color::Red);
		window.draw(rec);*/
		
}