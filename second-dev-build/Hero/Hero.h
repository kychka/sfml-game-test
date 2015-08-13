#ifndef HERO_H
#define HERO_H

#include <vector>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "Entity.h"

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
	void takeDamage(int damage);
private:
	bool invulnerability;
	float invulnerabilityTimer;
	bool H_Jump;
	void HeroJump();                                    // для обсчета прыжка  
	float H_JumpIndex;                                // для обсчета прыжка
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

/////Гравитация///////
class  Gravi
{
public:
	  Gravi();
	  Gravi(float gravi);
	  ~Gravi();
	void update(Entity &hero, Time &time);
private:
	float gravi;
};

///Камера///
 class Kamera:public Entity
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
	 void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) {}; // звглушка
 };

#endif