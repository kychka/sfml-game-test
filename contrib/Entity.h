#ifndef ENTITY_H
#define ENTITY_H
#include "..\Hero\AnimatedSprite.hpp"
#include "..\Hero\Animation.hpp"
#include "..\Level\Level.h"
#include<SFML/Graphics.hpp>

using namespace sf;

class Entity{
public:
	
	Entity();
	Entity(std::string name, int hp, int arm, Animation animation_mass[]);
	~Entity();
	void setHp(int hp);
	void setArm(int arm);
	void setPossition(float x, float y);
	void setAnimationSpeed(float as);
	void setSpeed(float hs);
	void move(float mx, float  my);
	void draw(RenderWindow &window);
	void collision(std::vector<lv::Object> &allObj);               //функция отрабатывает столкновения со всеми обьектами на карта,так же не дает упасть под обьекты Solid и Ground.Вызывать в функции  updateAndDraw()
	void setAnimation(Animation animation_mass[]);
	Vector2f getCenter();
	int getHp();
	int getArm();
	Vector2f getPossition();
	
	virtual void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) = 0; //принимает вектор со всеми обьектами на карте
private:
	bool _Jump;
	void Jump();                                    // для обсчета прыжка  
	float _JumpIndex;
	Vector2f X_Y_Poss;
	Animation *_MassAnim;               // Указатель на силку Анимации
	AnimatedSprite _Animation;        // Класс анимации
	String _Name;
	bool _onGround;
	int _hp;
	int _arm;
	int _DX;          //Вектор движения
	int _DXL;         // Вектор прошедшего движения
	float _Speed;
	float _frameTime;
	Time time;
	void swapAnimation();                 //Смена анимации
	int getVectorMove();                 // Тукущий вектор движения(если не движется то он будет 0, если движется то темод будет возвражять 1 если в верх, 2 если в право, 3 если вниз, 4 если в лево)
	int getVectorMoveLast();            //Вектор движнния в прошедшем времени служит для определиния анимации если стоит 
	Event _KeyPressedEvent;
};
#endif