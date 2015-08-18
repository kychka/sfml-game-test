#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy() :Enemy()
{

}

SimpleGroundEnemy::SimpleGroundEnemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]) : Enemy(position, name, hp, arm, animation_mass)
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