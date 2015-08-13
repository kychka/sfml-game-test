#include "Hero.h"

Hero::Hero() :Entity(){
	// Конструктор по умолчанию 
	H_Hp = 10;
	H_Arm = 10;
	H_DX = NULL;
	H_DXL = NULL;
	H_Speed = 1.0;
	K_ON = true;
	_onGround = false;
	H_JumpIndex = 5.0;
	H_Jump = false;
	invulnerability = false;
	invulnerabilityTimer = 0;
}

Hero::Hero(std::string name, Animation animation_mass[], Vector2f position, int hp, int arm) :Entity(name, animation_mass, position){
	H_Hp = hp;
	H_Arm = arm;
	H_DX = NULL;
	H_DXL = NULL;
	H_Speed = 1.0;
	K_ON = true;
	_onGround = false;
	H_JumpIndex = 5.0;
	H_Jump = false;
	invulnerability = false;
	invulnerability = 0;
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

void Hero::takeDamage(int damage){
	if (!invulnerability){
		H_Hp -= damage;
		invulnerability = true;
	}
}

void Hero::setHeroSpeed(float hs)
{
	H_Speed = hs / 300;
}


void Hero::collision(std::vector<lv::Object> &allObj)
{
	for (int i = 0; i < allObj.size(); i++)
	{
		if (getGlobalBounds().intersects(allObj[i].rect)){
			if (allObj[i].name == "ground")
			{
				_onGround = true;
				move(0, -0.5*time.asMilliseconds());// Отталкиваем от земли 
			}
			if (allObj[i].name == "Solid")
			{
				if (H_DX == 2) { move(-H_Speed* time.asMilliseconds(), 0); } // от боковых сторон 
				if (H_DX == 4) { move(H_Speed *time.asMilliseconds(), 0); }
			}
		}
	}
}

Vector2f Hero::getHeroCenter()
{
	return Vector2f(_Animation.getGlobalBounds().left + _Animation.getGlobalBounds().height / 2, _Animation.getGlobalBounds().top + _Animation.getGlobalBounds().width / 2);
}


void Hero::swapHeroAnimation()
{
	// Предпологается загрузка анимаций из файла 

	if (!_Animation.isPlaying())
	{
		playAnim(3); // Анимация по дефолту (если не выставить то при проверке на колизию будет краш, так как он будет запрашивать данные о кадре а тоесть его позици размер итд.)
	}
	if (H_DXL == 2 && H_DX == 0)  // Правая анимация стоя
	{
		playAnim(0); // в зависимости от индеска масива анимаций
		return;
	}
	if (H_DXL == 4 && H_DX == 0) // Левая анимация стоя
	{
		playAnim(1);
		return;
	}
	if (H_DX == 1) // Анимация прыжка
	{
		//H_Animation.play(H_MassAnim[0]);
		return;
	}
	if (H_DX == 3) // Анимация вниз или присел
	{
		playAnim(2);
		return;
	}
	if (H_DX == 2) // Анимация в право 
	{
		playAnim(2);
		return;
	}
	if (H_DX == 4) // Анимация в лево
	{
		playAnim(3);
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
	if (Keyboard::isKeyPressed(Keyboard::Space) && (_onGround))
	{
		//H_DX = 1;
		//H_DXL = 1;
		_onGround = false;
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
		move(H_Speed*time.asMilliseconds(), 0);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		H_DX = 4;
		H_DXL = 4;
		move(-H_Speed*time.asMilliseconds(), 0);
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

void Hero::updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window)
{
	this->time = time;
	if (invulnerability){
		_Animation.setColor(Color::Red);
		invulnerabilityTimer += time.asMilliseconds();
		if (invulnerabilityTimer > 3000){
			invulnerability = false;
		}
	}
	else{
		_Animation.setColor(Color::White);
	}
	heroKeyPressed(K_ON);
	swapHeroAnimation();
	window.draw(_Animation);
	HeroJump();
	_Animation.updateAnimation(time);
	collision(allObj);
	
	if (H_Hp == 0)
	{
		K_ON = false;
	}

}

void Hero::HeroJump()
{

	if (_onGround == false && H_Jump == true)
	{
		move(0, -H_Speed*time.asMilliseconds()*H_JumpIndex);
		H_JumpIndex -= 0.1;

		if (H_JumpIndex <= 1)
		{
			H_JumpIndex = 5.0;
			H_Jump = false;
			return;
		}
	}
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

void Gravi::update(Entity &hero, Time &time)
{
	hero.move(0, gravi*time.asMilliseconds());
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