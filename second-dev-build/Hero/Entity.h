#ifndef ENTITY_H
#define ENTITY_H

#include<SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "../Level/Level.h"

using namespace sf;

class Entity{
public:
	Entity(std::string name, Animation animation_mass[],Vector2f position);
	Entity();
	~Entity();
	void setPossition(float x, float y);
	void setAnimationSpeed(float as);
	void move(float mx, float  my);
	void draw(RenderWindow &window);
	bool _onGround;
               
	void setAnimation(Animation animation_mass[]);
	Vector2f getCenter();
	Vector2f getPossition();
	void playAnim(int num);
	void setWidht(float w);
	void setHeight(float h);
	float getWidht();
	float getHeight();
	FloatRect getGlobalBounds();
	FloatRect getLocalBounds();
	
	virtual void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) = 0; //принимает вектор со всеми обьектами на карте
	Vector2f X_Y_Poss;
	Animation *_MassAnim;               // Указатель на силку Анимации
	AnimatedSprite _Animation;        // Класс анимации
	String _Name;
	float _frameTime;
	Time time;
};

#endif