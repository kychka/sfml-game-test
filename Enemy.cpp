#include "Enemy.h"

Enemy::Enemy() :Entity(){
	E_DX = NULL;
	E_DXL = NULL;
	E_Speed = 1.0;
	E_Life = true;
	_onGround = false;
	E_damage = 5;

	
}

Enemy::Enemy(Hero &her,Vector2f position, String name, int hp, int arm, Animation animation_mass[]) :Entity(name, animation_mass, position){
	E_HP = hp;
	E_ARM = arm;
	E_Speed = 1.0;
	E_Life = true;
	_onGround = false;
	E_damage = 15;
	targetHero = her;
}
Enemy::~Enemy(){
}

void Enemy::setDamage(int damage){
	E_damage = damage;
}

int Enemy::getDamage(){
	return E_damage;
}

void Enemy::collision(std::vector<lv::Object> &allObj){
	for (int i = 0; i < allObj.size(); i++){

		if (getGlobalBounds().intersects(allObj[i].rect)){
			if (allObj[i].name == "ground")
			{
				_onGround = true;
				move(0, -0.5*time.asMilliseconds());// Отталкиваем от земли 
			}
			if (allObj[i].name == "Solid")
			{
				if (E_DX == 2) { move(-E_Speed* time.asMilliseconds(), 0); } // от боковых сторон 
				if (E_DX == 4) { move(E_Speed *time.asMilliseconds(), 0); }
			}
		}
	}
}

bool Enemy::isAlive(){
	return E_Life;
}

void Enemy::swapAnimation()
{
	// Предпологается загрузка анимаций из файла 

	if (!_Animation.isPlaying())
	{
		playAnim(3); // Анимация по дефолту (если не выставить то при проверке на колизию будет краш, так как он будет запрашивать данные о кадре а тоесть его позици размер итд.)
	}
		if (E_DXL == 2 && E_DX == 0)  // Правая анимация стоя
	{
		playAnim(0); // в зависимости от индеска масива анимаций
		return;
	}
	if (E_DXL == 4 && E_DX == 0) // Левая анимация стоя
	{
		playAnim(1);
		return;
	}
	if (E_DX == 1) // Анимация прыжка
	{
		//H_Animation.play(H_MassAnim[0]);
		return;
	}
	if (E_DX == 3) // Анимация вниз или присел
	{
		playAnim(2);
		return;
	}
	if (E_DX == 2) // Анимация в право 
	{
		playAnim(2);
		return;
	}
	if (E_DX == 4) // Анимация в лево
	{
		playAnim(3);
		return;
	}
}

void Enemy::setTarget(Hero her){
	Enemy::targetHero = her;
}