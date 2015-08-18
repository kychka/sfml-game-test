#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "HpBar/hp_bar.h"

using namespace sf;

class Enemy:public Entity{
public:
	Enemy();
	Enemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
	~Enemy();
	void collision(std::vector<lv::Object> &allObj);
	void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window);
	bool isAlive();
	void setDamage(int damage);
	int getDamage();
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
};

#endif