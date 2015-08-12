#ifndef HERO_H
#define HERO_H
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "..\Entity\Entity.h"
#include <vector>

using namespace sf;// Пространство имен

class Hero:public Entity
{
public:
	Hero();
	Hero(std::string name, Animation animation_mass[], Vector2f position, int hp, int arm);
	~Hero();
	void setHeroHp(int hp);
	void setHeroArm(int arm);
	void setHeroSpeed(float hs);
	void collision(std::vector<lv::Object> &allObj);
	Vector2f getHeroCenter();
	int getHeroHp();
	int getHeroArm();  
	void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window);
	void swapHeroAnimation();
private:
	bool H_Jump;
	void HeroJump();                                    // для обсчета прыжка  
	float H_JumpIndex;                                // для обсчета прыжка
	bool H_onGround;
	bool K_ON;                                      // Индикатор разрешить управление или нет( по дифолту тру)
	int H_Hp;                                      // Жизни
	int H_Arm;                                    // Броня
	int H_DX;                                    //Вектор движения
	int H_DXL;                                  // Вектор прошедшего движения
	float H_Speed;                             // Cкорость персонажа                    
	int getHeroVectorMove();                 // Тукущий вектор движения(если не движется то он будет 0, если движется то темод будет возвражять 1 если в верх, 2 если в право, 3 если вниз, 4 если в лево)
	int getHeroVectorMoveLast();            //Вектор движнния в прошедшем времени служит для определиния анимации если стоит 
	void heroKeyPressed(bool K_ON);
	Event H_KeyPressedEvent;           // Для определения что нажато и не только( можно упростить оставлю на усмотрение  того кто занимается управлением)
	
};

Hero::Hero() :Entity(){
	// Конструктор по умолчанию 
	
	H_Hp = 10;
	H_Arm = 10;
	H_DX = NULL;
	H_DXL = NULL;
	H_Speed = 1.0;
	K_ON = true;
	H_onGround = false;
	H_JumpIndex = 5.0;
	H_Jump = false;
	
}

Hero::Hero(std::string name,  Animation animation_mass[],Vector2f position,int hp, int arm) :Entity(name, animation_mass,position){
	H_Hp = hp;
	H_Arm = arm;
	H_DX = NULL;
	H_DXL = NULL;
	H_Speed = 1.0;
	K_ON = true;
	H_onGround = false;
	H_JumpIndex = 5.0;
	H_Jump = false;
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

inline void Hero::setHeroSpeed(float hs)
{
	H_Speed = hs/300;
}


inline void Hero::collision(std::vector<lv::Object> &allObj)
{
	for (int i = 0; i < allObj.size(); i++)
	{   
	
		if (getRect().intersects(allObj[i].rect)){
			if (allObj[i].name == "ground")
			{
			 H_onGround = true;
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


inline Vector2f Hero::getHeroCenter()
{
	return Vector2f(_Animation.getGlobalBounds().left+_Animation.getGlobalBounds().height/2, _Animation.getGlobalBounds().top+ _Animation.getGlobalBounds().width/2);
}


inline void Hero::swapHeroAnimation()
{
 // Предпологается загрузка анимаций из файла 

	if (!_Animation.isPlaying())
	{
		playAnim(3); // Анимация по дефолту (если не выставить то при проверке на колизию будет краш, так как он будет запрашивать данные о кадре а тоесть его позици размер итд.)
	}


	if (H_DXL == 2 && H_DX == 0 )  // Правая анимация стоя
	{
		playAnim(0); // в зависимости от индеска масива анимаций
		
		return;
	}
	if (H_DXL == 4 && H_DX == 0  ) // Левая анимация стоя
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

inline int Hero::getHeroVectorMove()
{
	return H_DX;
}

inline int Hero::getHeroVectorMoveLast()
{
	return H_DXL;
}

inline void Hero::heroKeyPressed(bool K_ON)
{
// Управление персонажем если есть лушче вариант к примеру через кейс, но пока оставлю так
	if (Keyboard::isKeyPressed(Keyboard::Space)&&(H_onGround))
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
		move(H_Speed*time.asMilliseconds(), 0);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		H_DX = 4;
		H_DXL = 4;
		move(-H_Speed*time.asMilliseconds(),0);
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
	
	if (H_onGround == false && H_Jump == true)
	{
		
		move(0, -H_Speed*time.asMilliseconds()*H_JumpIndex);
		H_JumpIndex -= 0.1;

		if (H_JumpIndex <=1)
		{
			H_JumpIndex = 5.0;
			H_Jump = false;
			return;
		}
		
	}
	 
   
}



/////Гравитация///////
class  Gravi
{
public:
	  Gravi();
	  Gravi(float gravi);
	~ Gravi();
	void update(Hero &hero, Time &time);
private:
	float gravi;
};

Gravi::Gravi()
{
	gravi = NULL;

}
 Gravi::Gravi(float gravi)
{
	this->gravi = gravi;

}

 Gravi::~ Gravi()
{
}

 inline void Gravi::update(Hero & hero,Time &time)
 {
	 hero.move(0, gravi*time.asMilliseconds());

 }

///Камера///
 class Kamera
 {

	 // Берет в себя все силки 
	 // Один метод абдейт 
 public:
	 Kamera();
	 Kamera(Hero &hero, lv::Level &level, RenderWindow &window);
	 ~Kamera();
	 void updateKamera();
 private:
	 View view;
	 Vector2f K_X_YPoss;
	 FloatRect MapRect;
	 Vector2f L_W_H_Size;
	 lv::Level *level;
	 Hero  *hero;
	 RenderWindow *window;
 };
 
 

 inline Kamera::Kamera(Hero &hero, lv::Level &level, RenderWindow &window) 
 {
	 this->hero = &hero;
	 this->level = &level;
	 this->window = &window;
	 view.reset(FloatRect(0.0,0.0,window.getSize().x,window.getSize().y)); // камера по размеру окна
	 MapRect.height = level.GetMapSize().y*level.GetTileSize().y; MapRect.width= level.GetMapSize().x*level.GetTileSize().x; // данные о размере карты 
	 L_W_H_Size.x = level.GetMapSize().x*level.GetTileSize().x;
	 L_W_H_Size.y = level.GetMapSize().y*level.GetTileSize().y;
	
 }

 inline Kamera::Kamera()
 {

	 
 }
 inline Kamera::~Kamera()
 {
	
 }

 inline void Kamera::updateKamera() // Получает центр игрока, из него вычетает половину раземера камеры по каждой из сторон, проверяет привишает это размеры карты и если нет то камере можно следить за игроком 

 {
	 if (hero->getHeroCenter().x -( view.getSize().x /2 ) > 0 && hero->getHeroCenter().x + (view.getSize().x / 2) <MapRect.width)
	 {
			 view.setCenter(hero->getHeroCenter().x, view.getCenter().y);
	 }
	 
	 if (hero->getHeroCenter().y - (view.getSize().y / 2) > 0 && hero->getHeroCenter().y + (view.getSize().y / 2) < MapRect.height)
	 {
		 view.setCenter(view.getCenter().x, hero->getHeroCenter().y);
	 }
	 window->setView(view);
 }

#endif