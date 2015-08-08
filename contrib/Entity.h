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
	void collision(std::vector<lv::Object> &allObj);               //������� ������������ ������������ �� ����� ��������� �� �����,��� �� �� ���� ������ ��� ������� Solid � Ground.�������� � �������  updateAndDraw()
	void setAnimation(Animation animation_mass[]);
	Vector2f getCenter();
	int getHp();
	int getArm();
	Vector2f getPossition();
	
	virtual void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window) = 0; //��������� ������ �� ����� ��������� �� �����
private:
	bool _Jump;
	void Jump();                                    // ��� ������� ������  
	float _JumpIndex;
	Vector2f X_Y_Poss;
	Animation *_MassAnim;               // ��������� �� ����� ��������
	AnimatedSprite _Animation;        // ����� ��������
	String _Name;
	bool _onGround;
	int _hp;
	int _arm;
	int _DX;          //������ ��������
	int _DXL;         // ������ ���������� ��������
	float _Speed;
	float _frameTime;
	Time time;
	void swapAnimation();                 //����� ��������
	int getVectorMove();                 // ������� ������ ��������(���� �� �������� �� �� ����� 0, ���� �������� �� ����� ����� ���������� 1 ���� � ����, 2 ���� � �����, 3 ���� ����, 4 ���� � ����)
	int getVectorMoveLast();            //������ �������� � ��������� ������� ������ ��� ����������� �������� ���� ����� 
	Event _KeyPressedEvent;
};
#endif