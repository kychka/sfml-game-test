#include "Hero.h"

Hero::Hero()
{
	// Конструктор по умолчанию 
	H_Name = "Hero";
	H_Hp = 10;
	H_Arm = 10;
	H_X_Y_Poss.x = NULL;
	H_X_Y_Poss.y = NULL;
	H_DX = NULL;
	H_DXL = NULL;
	H_Speed = 1.0;
	H_FrameTime = NULL;
	K_ON = true;
	H_onGround = false;
	H_JumpIndex = 5.0;
	H_Jump = false;
}

Hero::Hero(std::string name, int hp, int arm, Animation  animation_mass[])
{
	H_Name = name;
	H_Hp = hp;
	H_Arm = arm;
	H_MassAnim = animation_mass;
}


Hero::~Hero()
{
}

void Hero::setHeroHp(int hp)
{
	H_Hp = hp;
}

void Hero::setHeroArm(int arm)
{
	H_Arm = arm;
}

void Hero::setHeroPossition(float x, float y)
{
	H_X_Y_Poss.x = x;
	H_X_Y_Poss.y = y;
	H_Animation.setPosition(x, y);
}

void Hero::setHeroAnimationSpeed(float as)
{
	H_Animation.setAnimPropers(sf::seconds(as / 10), true, false);
}

void Hero::setHeroSpeed(float hs)
{
	H_Speed = hs / 300;
}

void Hero::moveHero(float mx, float my)
{
	H_X_Y_Poss.x += mx;
	H_X_Y_Poss.y += my;
	H_Animation.move(mx, my);
}

void Hero::drawHero(RenderWindow &window)
{
	window.draw(H_Animation);
}

void Hero::collisionHero(std::vector<lv::Object> &objSolid, std::vector<lv::Object> &objGround)
{
	for (int i = 0; i < objGround.size(); i++)
	{
		if (H_Animation.getGlobalBounds().intersects(objGround[i].rect))
		{
			H_onGround = true;
			moveHero(0, -0.5*time.asMilliseconds());// Отталкиваем от земли
		}
	}
	for (int i = 0; i < objSolid.size(); i++)
	{
		if (H_Animation.getGlobalBounds().intersects(objSolid[i].rect))
		{
			if (H_DX == 2) { moveHero(-H_Speed* time.asMilliseconds(), 0); } // от боковых сторон 
			if (H_DX == 4) { moveHero(H_Speed *time.asMilliseconds(), 0); }
		}
	}
}

void Hero::setHeroAnimation(Animation animation_mass[])
{
	H_MassAnim = animation_mass;
}

Vector2f Hero::getHeroCenter()
{
	return Vector2f(H_Animation.getGlobalBounds().left + H_Animation.getGlobalBounds().height / 2, H_Animation.getGlobalBounds().top + H_Animation.getGlobalBounds().width / 2);
}

void Hero::swapHeroAnimation()
{
	// Предпологается загрузка анимаций из файла 
	if (!H_Animation.isPlaying())
	{
		H_Animation.play(H_MassAnim[3]); // Анимация по дефолту (если не выставить то при проверке на колизию будет краш, так как он будет запрашивать данные о кадре а тоесть его позици размер итд.)
	}
	if (H_DXL == 2 && H_DX == 0)  // Правая анимация стоя
	{
		H_Animation.play(H_MassAnim[0]); // в зависимости от индеска масива анимаций
		return;
	}
	if (H_DXL == 4 && H_DX == 0) // Левая анимация стоя
	{
		H_Animation.play(H_MassAnim[1]);
		return;
	}
	if (H_DX == 1) // Анимация прыжка
	{
		//H_Animation.play(H_MassAnim[0]);
		return;
	}
	if (H_DX == 3) // Анимация вниз или присел
	{
		H_Animation.play(H_MassAnim[2]);
		return;
	}
	if (H_DX == 2) // Анимация в право 
	{
		H_Animation.play(H_MassAnim[2]);
		return;
	}
	if (H_DX == 4) // Анимация в лево
	{
		H_Animation.play(H_MassAnim[3]);
		return;
	}
}

int Hero::getHeroVectorMove()
{
	return H_DX;
}

int Hero::getHeroVectorMoveLast()
{
	return H_DXL;
}

void Hero::heroKeyPressed(bool K_ON)
{
	// Управление персонажем если есть лушче вариант к примеру через кейс, но пока оставлю так
	if (Keyboard::isKeyPressed(Keyboard::Space) && (H_onGround))
	{
		//H_DX = 1;
		//H_DXL = 1;
		H_onGround = false;
		H_Jump = true;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		H_DX = 3;
		H_DXL = 3;
		//moveHero(0, H_Speed*time.asMilliseconds());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		H_DX = 2;
		H_DXL = 2;
		moveHero(H_Speed*time.asMilliseconds(), 0);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		H_DX = 4;
		H_DXL = 4;
		moveHero(-H_Speed*time.asMilliseconds(), 0);
		return;
	}
	H_DX = 0; // если не чего не нажали то вектор 0 тоесть стоим 
}

int Hero::getHeroHp()
{
	return H_Hp;
}

int Hero::getHeroArm()
{
	return H_Arm;
}

void Hero::updateAndDrawHero(Time &time, std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj, RenderWindow &window)
{
	this->time = time;
	heroKeyPressed(K_ON);
	swapHeroAnimation();
	drawHero(window);
	HeroJump();
	H_Animation.updateAnimation(time);
	collisionHero(solidObj, groundObj);
	
	if (H_Hp == 0)
	{
		K_ON = false;
	}
}

void Hero::HeroJump()
{
	if (H_onGround == false && H_Jump == true)
	{
		moveHero(0, -H_Speed*time.asMilliseconds()*H_JumpIndex);
		H_JumpIndex -= 0.1;

		if (H_JumpIndex <= 1)
		{
			H_JumpIndex = 5.0;
			H_Jump = false;
			return;
		}
	}
}

Vector2f Hero::getHeroPossition()
{
	return H_X_Y_Poss;
}

/////Гравитация///////
Gravi::Gravi()
{
	gravi = NULL;
}
Gravi::Gravi(float gravi)
{
	this->gravi = gravi;
}
Gravi::~Gravi()
{
}

void Gravi::update(Hero & hero, Time &time)
{
	hero.moveHero(0, gravi*time.asMilliseconds());
}

///Камера///
Kamera::Kamera(Hero &hero, lv::Level &level, RenderWindow &window)
{
	this->hero = &hero;
	this->level = &level;
	this->window = &window;
	view.reset(FloatRect(0.0, 0.0, window.getSize().x, window.getSize().y)); // камера по размеру окна
	MapRect.height = level.GetMapSize().y*level.GetTileSize().y; MapRect.width = level.GetMapSize().x*level.GetTileSize().x; // данные о размере карты 
	L_W_H_Size.x = level.GetMapSize().x*level.GetTileSize().x;
	L_W_H_Size.y = level.GetMapSize().y*level.GetTileSize().y;
}

Kamera::Kamera()
{
}
Kamera::~Kamera()
{
}

void Kamera::updateKamera() // Получает центр игрока, из него вычетает половину раземера камеры по каждой из сторон, проверяет привишает это размеры карты и если нет то камере можно следить за игроком 

{
	if (hero->getHeroCenter().x - (view.getSize().x / 2) > 0 && hero->getHeroCenter().x + (view.getSize().x / 2) <MapRect.width)
	{
		view.setCenter(hero->getHeroCenter().x, view.getCenter().y);
	}
	if (hero->getHeroCenter().y - (view.getSize().y / 2) > 0 && hero->getHeroCenter().y + (view.getSize().y / 2) < MapRect.height)
	{
		view.setCenter(view.getCenter().x, hero->getHeroCenter().y);
	}
	window->setView(view);
}
Vector2f Kamera::getPossition()
{
	return Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
}