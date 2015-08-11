#ifndef ENTITY_H
#define ENTITY_H
#include "..\Hero\AnimatedSprite.hpp"
#include "..\Hero\Animation.hpp"
#include "..\Level\Level.h"
#include<SFML/Graphics.hpp>

using namespace sf;

class Entity{
public:
	Entity(std::string name, Animation animation_mass[],Vector2f position);
	Entity(){};
	~Entity();
	void setPossition(float x, float y);
	void setAnimationSpeed(float as);
	void move(float mx, float  my);
	void draw(RenderWindow &window);
	virtual void collision(std::vector<lv::Object> &allObj) = 0;               
	void setAnimation(Animation animation_mass[]);
	Vector2f getCenter();
	Vector2f getPossition();
	void playAnim(int num);
	void setWidht(float w);
	void setHeight(float h);
	float getWidht();
	float getHeight();
	FloatRect getRect();
	
	virtual void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) = 0; //принимает вектор со всеми обьектами на карте
	float _widht;
	float _height;
	Vector2f X_Y_Poss;
	Animation *_MassAnim;               // ”казатель на силку јнимации
	AnimatedSprite _Animation;        //  ласс анимации
	String _Name;
	float _frameTime;
	Time time;
};
#endif