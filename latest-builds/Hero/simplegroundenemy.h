#ifndef SIMPLEGROUNDENEMY_H
#define SIMPLEGROUNDENEMY_H

#include "HpBar/hp_bar.h"
#include "Enemy.h"
#include "WeaponEnemy.h"


class SimpleGroundEnemy :public Enemy
{
public:
	SimpleGroundEnemy(Hero &her, Kamera &kam);
	SimpleGroundEnemy(Hero &her, Kamera &kam, Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
	~SimpleGroundEnemy();
	void collision(std::vector<lv::Object> &allObj);
	bool isAlive();
	void setHp(int hp);
	int getHp();
	void setDamage(int damage);
	int getDamage();
	void collisionWithHero();
	void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window);
	bool seeTarget(std::vector<lv::Object> &allObj, RenderWindow &window);
	float distance;
	float getVectorMove();
private:


	bool SeeTargetToo();
	void FireTarget();
	void moveBase(std::vector<lv::Object> &allObj, RenderWindow &window);//Просто ходит туды сюды //Нужно добавить в конструктор размер площядки 
	Vector2f TooPointForbaseMove;// для неё
	Animation *CurentAnimation;// Вот силка
	float BaseVectorMove ;
	void GraviUpdate();
	float gravi;
	WeaponEnemy weapon;
	Texture texture;
	Hero *hero;
	bool IsTarget;
	int Vector;// если 0 значит стоит или идет в лево если 1 то в право 

};

#endif // SIMPLEGROUNDENEMY_H