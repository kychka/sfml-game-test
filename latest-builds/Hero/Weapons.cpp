#include "Weapons.h"

Weapon::Weapon()
{
	texture = NULL;
}
Weapon::Weapon(Texture &texture , int ammo_size, float damage)
{
	this->ammo_size = ammo_size;
	this->damage = damage;
	this->ammo_size = ammo_size;
	this->texture = &texture;
	vector_move = NULL;
}


Weapon::~Weapon()
{
}

void Weapon::inicialize(sf::Texture &texture, int ammo_size, float damage, Hero &hero)
{
	this->texture = &texture;
	this->ammo_size = ammo_size;
	this->damage = damage;
	this->ammo_size = ammo_size;
	this->hero = &hero;
	
}
void  Weapon::setDamage(float damage)
{
	this->damage = damage;
}
void Weapon::fire()
{
	int x = 0;
	if (hero->getheroAnimIndex() == 1 || hero->getheroAnimIndex() == 5 || hero->getheroAnimIndex() == 9 || hero->getheroAnimIndex() == 13)
	{
		if (hero->getFireState() == 0)
		{
			if (ammo_size != 0)
			{
				if (hero->getStayState() == 0)
				{
					vector_move = -0.1;
					x = -150;
				}
				if (hero->getStayState() == 1)
				{
					x = 150;
					vector_move = 0.1;
				}

				bullett.push_back(new Bullet(*texture, hero->getHeroCenter().x+x, hero->getHeroCenter().y, vector_move));
				ammo_size--;
			}
		}
	}
			
		
}
void Weapon::update(sf::RenderWindow &window, Kamera &kamera, std::vector<lv::Object> &obj, float time, Hero &hero, std::list<SimpleGroundEnemy*> EnemyMass)
{
	  
		if (!bullett.empty())
		{
			it = bullett.begin();
			
			for (int i = 0; i < bullett.size(); i++)
			{
				itMob = EnemyMass.begin();

				(*it)->update(window, time, hero);
			
				for (int i = 0; i < obj.size(); i++)
				{
					if ((*it)->getGlobalBounds(obj[i].rect))
					{
						bullett.remove((*it));
						it=bullett.begin();
						return;
						
					}
				}
				for (int i = 0; i < EnemyMass.size(); i++)
				{
					if ((*it)->getGlobalBounds((*itMob)->getGlobalBounds()))
					{
						(*itMob)->setHp((*itMob)->getHp()-10);///////// Пока удар на 10 для теста
						bullett.remove((*it));
						return;
					}

					itMob++;
				}

				if((*it)->getPoss().x > kamera.getPossition().x + kamera.getSize().x || (*it)->getPoss().x < kamera.getPossition().x)
				{
					bullett.remove((*it));
					it = bullett.begin();
					return;

				}

				it++;
			}
												
				

		}


		fire();
		reload();
		if (ammo_size == 0){ hero.isAmmo_chek(false);}//если нет патронов то запретить загрузку анимации стрелять 
		if (ammo_size > 0){ hero.isAmmo_chek(true); }// если есть то разрешить 

}
void Weapon::reload()
{
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		ammo_size = 100;
	}
	

}
int Weapon::getAmmoSize()
{
	return ammo_size;
}

Bullet::Bullet(sf::Texture &texture,float x, float y,float vectormove)
{
	this->texture = &texture;
	sprite.setTexture(texture);
	
	sprite.setPosition(x, y-80);
	vector_move = vectormove;
	speed = 7;
}


Bullet::~Bullet()
{
}

void Bullet::update(sf::RenderWindow &window, float time,Hero &hero)
{

	window.draw(sprite);
	move(vector_move*time*10*speed, 0);
}

void Bullet::setPoss(float x, float y)
{

	sprite.setPosition(x, y);

}
void Bullet::move(float x, float y)
{

	sprite.move(x, y);


}
bool Bullet::getGlobalBounds(sf::Rect<float> rect)
{
	if (sprite.getGlobalBounds().intersects(rect))
	{
		return true;
	}
	 return false; 
}

Vector2f Bullet::getPoss()
{
	return Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}