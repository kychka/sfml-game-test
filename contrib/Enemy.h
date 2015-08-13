#ifndef ENEMY_H
#define ENEMY_H
#include "..\Entity\Entity.h"
#include "..\Hero\HpBar\hp_bar.h"

using namespace sf;

class Enemy:public Entity{
public:
	Enemy();
	Enemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]);
	~Enemy();
	void collision(std::vector<lv::Object> &allObj);
	void updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window);
	bool isAlive();
	void setDamage(int damage);
	int getDamage();
private:
	void swapAnimation();
	int E_damage;
	bool E_Life;
	float E_Speed;
	Color E_bodyColor;
	int E_HP;
	int E_ARM;
	RectangleShape body;
	int E_DX;
	int E_DXL;


};


Enemy::Enemy() :Entity(){
	E_DX = NULL;
	E_DXL = NULL;
	E_Speed = 1.0;
	E_Life = true;
	_onGround = false;
	E_damage = 5;
}

Enemy::Enemy(Vector2f position, String name, int hp, int arm, Animation animation_mass[]):Entity(name,animation_mass,position){
	E_HP = hp;
	E_ARM = arm;
	E_Speed = 1.0;
	E_Life = true;
	_onGround = false;
	E_damage = 15;
}
Enemy::~Enemy(){
}

void Enemy::setDamage(int damage){
	E_damage = damage;
}

int Enemy::getDamage(){
	return E_damage;
}

void Enemy::collision(std::vector<lv::Object> &allObj){
	for (int i = 0; i < allObj.size(); i++){

		if (getGlobalBounds().intersects(allObj[i].rect)){
			if (allObj[i].name == "ground")
			{
				_onGround = true;
				move(0, -0.5*time.asMilliseconds());// ����������� �� ����� 
				


			}
			if (allObj[i].name == "Solid")
			{

				if (E_DX == 2) { move(-E_Speed* time.asMilliseconds(), 0); } // �� ������� ������ 
				if (E_DX == 4) { move(E_Speed *time.asMilliseconds(), 0); }

			}
		}
	}
}

bool Enemy::isAlive(){
	return E_Life;
}

inline void Enemy::swapAnimation()
{
	// �������������� �������� �������� �� ����� 

	if (!_Animation.isPlaying())
	{
		playAnim(3); // �������� �� ������� (���� �� ��������� �� ��� �������� �� ������� ����� ����, ��� ��� �� ����� ����������� ������ � ����� � ������ ��� ������ ������ ���.)
	}


	if (E_DXL == 2 && E_DX == 0)  // ������ �������� ����
	{
		playAnim(0); // � ����������� �� ������� ������ ��������

		return;
	}
	if (E_DXL == 4 && E_DX == 0) // ����� �������� ����
	{
		playAnim(1);

		return;
	}
	if (E_DX == 1) // �������� ������
	{
		//H_Animation.play(H_MassAnim[0]);

		return;
	}
	if (E_DX == 3) // �������� ���� ��� ������
	{
		playAnim(2);

		return;
	}
	if (E_DX == 2) // �������� � ����� 
	{
		playAnim(2);

		return;
	}
	if (E_DX == 4) // �������� � ����
	{
		playAnim(3);

		return;
	}

}

void Enemy::updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window){
	this->time = time;
	swapAnimation();
	renderHpBar(E_HP, X_Y_Poss, Vector2f(100, 20), window);
	window.draw(_Animation);
	_Animation.updateAnimation(time);
	collision(allObj);
	

	if (E_HP <= 0){
		E_Life = false;
	}

}

#endif