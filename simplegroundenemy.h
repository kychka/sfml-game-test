#ifndef SIMPLEGROUNDENEMY_H
#define SIMPLEGROUNDENEMY_H
#include "Hero/HpBar/hp_bar.h"
#include "Hero/Enemy.h"

class SimpleGroundEnemy:public Enemy
{
    SimpleGroundEnemy();
    SimpleGroundEnemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
    ~SimpleGroundEnemy();
    void collision(std::vector<lv::Object> &allObj);
    void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window);
    bool isAlive();
    void setDamage(int damage);
    int getDamage();
};

#endif // SIMPLEGROUNDENEMY_H

