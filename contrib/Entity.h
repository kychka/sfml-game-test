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
	void setPossition(float x, float y);
	void setAnimationSpeed(float as);
	void move(float mx, float  my);
	void draw(RenderWindow &window);
	virtual void collision(std::vector<lv::Object> &allObj) = 0;               
	void setAnimation(Animation animation_mass[]);
	Vector2f getCenter();
	Vector2f getPossition();
	void playAnim(int num);
	
	virtual void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) = 0; //��������� ������ �� ����� ��������� �� �����
private:
	Vector2f X_Y_Poss;
	Animation *_MassAnim;               // ��������� �� ����� ��������
	AnimatedSprite _Animation;        // ����� ��������
	String _Name;
	float _frameTime;
	Time time;
	void swapAnimation();                 //����� ��������
};
#endif