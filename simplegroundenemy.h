#ifndef SIMPLEGROUNDENEMY_H
#define SIMPLEGROUNDENEMY_H

#include "HpBar/hp_bar.h"
#include "Enemy.h"

class SimpleGroundEnemy :public Enemy
{
public:
	SimpleGroundEnemy(Hero &her, Kamera &kam);
	SimpleGroundEnemy(Hero &her, Kamera &kam, Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
	~SimpleGroundEnemy();
	void collision(std::vector<lv::Object> &allObj);
	bool isAlive();
	void setDamage(int damage);
	int getDamage();
	void collisionWithHero();
	void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window);
	bool seeTarget(std::vector<lv::Object> &allObj, RenderWindow &window);
	float distance;
};

#endif // SIMPLEGROUNDENEMY_H