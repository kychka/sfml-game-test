
#include"Hero.h"
#include <list>

class BulletEnemy
{
public:
	BulletEnemy(sf::Texture &texture, float x, float y, float vectormove);
	~BulletEnemy();
	void update(sf::RenderWindow &window, Time &time, Hero &hero);
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

class WeaponEnemy
{
public:
	WeaponEnemy();
	WeaponEnemy(sf::Texture &texture, int ammo_size, float damage);
	~WeaponEnemy();
	void setDamage(float damage);
	void fire(float vector_move, float x, float y, int  animIndex, bool isTarget);
	void update(sf::RenderWindow &window, Kamera &kamera, std::vector<lv::Object> &obj, Time &time, Hero &hero, int animIndex, float vector_move, float x, float y, bool isTarget);
	void inicialize(sf::Texture &texture, float damage, Hero &hero);
private:
	Texture *texture;
	float damage;
	std::list<BulletEnemy*> bullett;
	std::list<BulletEnemy*>::iterator it;
	Hero *hero;
	float vector_move;
	AnimatedSprite *CurentAnimation;
};

