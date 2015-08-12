#ifndef HERO_H
#define HERO_H

#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "../Level/Level.h"

using namespace sf;                        // Пространство имен
class Hero
{
public:
	Hero();
	Hero(std::string name, int hp, int arm, Animation animation_mass[]);
	~Hero();
	void setHeroHp(int hp);
	void setHeroArm(int arm);
	void setHeroPossition(float x, float y);
	void setHeroAnimationSpeed(float as);
	void setHeroSpeed(float hs);
	void moveHero(float mx, float  my);
	void drawHero(RenderWindow &window);
	void collisionHero(std::vector<lv::Object> &objSolid, std::vector<lv::Object> &objGround);
	void setHeroAnimation(Animation animation_mass[]);
	Vector2f getHeroCenter();
	int getHeroHp();
	int getHeroArm(); 
	Vector2f getHeroPossition(); 
	void updateAndDrawHero(Time &time, std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj, RenderWindow &window);
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
	float H_FrameTime;                        // Время цикла  
	void swapHeroAnimation();                 //Смена анимации
	int getHeroVectorMove();                 // Тукущий вектор движения(если не движется то он будет 0, если движется то темод будет возвражять 1 если в верх, 2 если в право, 3 если вниз, 4 если в лево)
	int getHeroVectorMoveLast();            //Вектор движнния в прошедшем времени служит для определиния анимации если стоит 
	void heroKeyPressed(bool K_ON);
	Vector2f H_X_Y_Poss;                   // Позиция по х и у
	String H_Name;                        // Имя
	Animation *H_MassAnim;               // Указатель на силку Анимации
	AnimatedSprite H_Animation;        // Класс анимации
	Event H_KeyPressedEvent;           // Для определения что нажато и не только( можно упростить оставлю на усмотрение  того кто занимается управлением)
	Time time;
};

/////Гравитация///////
class  Gravi
{
public:
	Gravi();
	Gravi(float gravi);
	~Gravi();
	void update(Hero &hero, Time &time);
private:
	float gravi;
};

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
	Vector2f getPossition();
private:
	View view;
	Vector2f K_X_YPoss;
	FloatRect MapRect;
	Vector2f L_W_H_Size;
	lv::Level *level;
	Hero  *hero;
	RenderWindow *window;
};

#endif // HERO_H