#ifndef WEAPON_H
#define WEAPON_H


//#include <iostream>
//#include "Hero.h"

#include "SFML/Graphics.hpp"
#include "../Level/Level.hpp"
#include "../Hero/Hero.h"
#include "simplegroundenemy.h"
#include <iostream>
#include <list>
class Bullet
{
public:
	Bullet(sf::Texture &texture, float x, float y, float vectormove);
	~Bullet();
	bool glTest();
	void update(sf::RenderWindow &window, float time, Hero &hero);
	void setPoss(float x, float y);
	void move(float x, float y);
	bool getGlobalBounds(sf::Rect<float> rect);
	Vector2f getPoss();
private:
	sf::Texture *texture;
	sf::Sprite sprite;
	float vector_move;// 0 left,1 right
	float speed;
};



class Weapon
{
public:
	Weapon();
	Weapon(sf::Texture &texture, int ammo_size, float damage);
	~Weapon();
	void reload();
	void setDamage(float damage);
	void fire();
	void update(sf::RenderWindow &window, Kamera &kamera, std::vector<lv::Object> &obj, float time, Hero &hero, std::list<SimpleGroundEnemy*> EnemyMass);
	void inicialize(sf::Texture &texture, int ammo_size, float damage, Hero &hero);
	int getAmmoSize();
private:
	int ammo_size;
	Texture *texture;
	float damage;
	std::list<Bullet*> bullett;
	std::list<Bullet*>::iterator it;
	std::list<SimpleGroundEnemy*>::iterator itMob;
	Hero *hero;
	float vector_move;
};

#endif 