#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "HpBar/hp_bar.h"
#include "Hero.h"

using namespace sf;

class Enemy:public Entity{
public:
	Enemy(Hero &her);
	Enemy(Hero &her,Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
	~Enemy();
	void collision(std::vector<lv::Object> &allObj);
	virtual void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) = 0;
	bool isAlive();
	void setDamage(int damage);
	int getDamage();
	/*void setTarget(Hero &her);*/
protected:
	void swapAnimation();
	int E_damage;
	bool E_Life;
	float E_Speed;
	Color E_bodyColor;
	int E_HP;
	int E_ARM;
	RectangleShape body;
	int E_DX;
	int E_DXL;
	Hero& targetHero;
};

#endif