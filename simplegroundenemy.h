#ifndef SIMPLEGROUNDENEMY_H
#define SIMPLEGROUNDENEMY_H

#include "HpBar/hp_bar.h"
#include "Enemy.h"

class SimpleGroundEnemy :public Enemy
{
public:
	SimpleGroundEnemy();
	SimpleGroundEnemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
	~SimpleGroundEnemy();
	void collision(std::vector<lv::Object> &allObj);
	bool isAlive();
	void setDamage(int damage);
	int getDamage();
};

#endif // SIMPLEGROUNDENEMY_H