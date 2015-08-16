#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]) :Enemy(position, name, hp, arm, *animation_mass[])
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
SimpleGroundEnemy::collision(std::vector<lv::Object> &allObj)
{
    void  Enemy::collision(&allObj);
}
SimpleGroundEnemy::getDamage()
{
    void Enemy::getDamage();
}
SimpleGroundEnemy::isAlive()
{
    void Enemy::isAlive();
}
SimpleGroundEnemy::setDamage(int damage)
{
    void Enemy::setDamage(damage);
}
