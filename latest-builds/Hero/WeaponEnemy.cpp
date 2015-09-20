#include "WeaponEnemy.h"


WeaponEnemy::WeaponEnemy()
{
	texture = NULL;
}
WeaponEnemy::WeaponEnemy(sf::Texture &texture, int ammo_size, float damage)
{
	
	this->damage = damage;
	this->texture = &texture;
	vector_move = NULL;
}

WeaponEnemy::~WeaponEnemy()
{
}
void WeaponEnemy::inicialize(sf::Texture &texture, float damage, Hero &hero)
{
	this->texture = &texture;
	this->damage = damage;
	this->hero = &hero;
	//this->CurentAnimation = &curentAnimation;
	vector_move = NULL;
}

void  WeaponEnemy::setDamage(float damage)
{
	this->damage = damage;
}

void WeaponEnemy::fire(float vector_move, float x, float y, int  animIndex, bool isTarget)
{
	int xx = 0;

	if (isTarget)
	{
	
		if (animIndex == 1)
		{
			if (vector_move == 1)
			{
				this->vector_move = -0.1;
				xx = 0;
			}

			if (vector_move == 0)
			{

				this->vector_move = 0.1;
				xx = 200;
			}
			if (this->vector_move)


			bullett.push_back(new BulletEnemy(*texture, x + xx, y + 180, this->vector_move));

		}

	}

	

}

void WeaponEnemy::update(sf::RenderWindow &window, Kamera &kamera, std::vector<lv::Object> &obj, Time &time, Hero &hero, int animIndex, float vector_move, float x, float y, bool isTarget)
{

	if (!bullett.empty())
	{
		it = bullett.begin();

		for (int i = 0; i < bullett.size(); i++)
		{
			(*it)->update(window, time, hero);

			for (int i = 0; i < obj.size(); i++)
			{
				if ((*it)->getGlobalBounds(obj[i].rect))
				{
					bullett.remove((*it));
					it = bullett.begin();
					return;

				}
			}
			
				if ((*it)->getGlobalBounds(hero.getGlobalBounds()))
				{
					hero.setHeroHp(hero.getHeroHp() - 0.2);
					bullett.remove((*it));
					return;
				}


			if ((*it)->getPoss().x > kamera.getPossition().x + kamera.getSize().x || (*it)->getPoss().x < kamera.getPossition().x)
			{
				bullett.remove((*it));
				it = bullett.begin();
				return;

			}

			it++;
		}



	}


	fire(vector_move, x, y, animIndex,isTarget);
	

}


BulletEnemy::BulletEnemy(sf::Texture &texture, float x, float y, float vectormove)
{
	this->texture = &texture;
	sprite.setTexture(texture);

	sprite.setPosition(x, y - 80);
	vector_move = vectormove;
	speed = 5;
}


BulletEnemy::~BulletEnemy()
{
}

void BulletEnemy::update(sf::RenderWindow &window, Time &time, Hero &hero)
{

	window.draw(sprite);
	move(vector_move*time.asMilliseconds() * 10 * speed, 0);
}

void BulletEnemy::setPoss(float x, float y)
{

	sprite.setPosition(x, y);

}
void BulletEnemy::move(float x, float y)
{

	sprite.move(x, y);


}
bool BulletEnemy::getGlobalBounds(sf::Rect<float> rect)
{
	if (sprite.getGlobalBounds().intersects(rect))
	{
		return true;
	}
	return false;
}

Vector2f BulletEnemy::getPoss()
{
	return Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}