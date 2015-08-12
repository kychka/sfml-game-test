#ifndef HERO_H
#define HERO_H
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "..\Entity\Entity.h"
#include <vector>

using namespace sf;// ������������ ����

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
	void HeroJump();                                    // ��� ������� ������  
	float H_JumpIndex;                                // ��� ������� ������
	bool H_onGround;
	bool K_ON;                                      // ��������� ��������� ���������� ��� ���( �� ������� ���)
	int H_Hp;                                      // �����
	int H_Arm;                                    // �����
	int H_DX;                                    //������ ��������
	int H_DXL;                                  // ������ ���������� ��������
	float H_Speed;                             // C������� ���������                    
	int getHeroVectorMove();                 // ������� ������ ��������(���� �� �������� �� �� ����� 0, ���� �������� �� ����� ����� ���������� 1 ���� � ����, 2 ���� � �����, 3 ���� ����, 4 ���� � ����)
	int getHeroVectorMoveLast();            //������ �������� � ��������� ������� ������ ��� ����������� �������� ���� ����� 
	void heroKeyPressed(bool K_ON);
	Event H_KeyPressedEvent;           // ��� ����������� ��� ������ � �� ������( ����� ��������� ������� �� ����������  ���� ��� ���������� �����������)
	
};

Hero::Hero() :Entity(){
	// ����������� �� ��������� 
	
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
			 move(0, -0.5*time.asMilliseconds());// ����������� �� ����� 
			
			
		 }
			if (allObj[i].name == "Solid")
			{
			
			if (H_DX == 2) { move(-H_Speed* time.asMilliseconds(), 0); } // �� ������� ������ 
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
 // �������������� �������� �������� �� ����� 

	if (!_Animation.isPlaying())
	{
		playAnim(3); // �������� �� ������� (���� �� ��������� �� ��� �������� �� ������� ����� ����, ��� ��� �� ����� ����������� ������ � ����� � ������ ��� ������ ������ ���.)
	}


	if (H_DXL == 2 && H_DX == 0 )  // ������ �������� ����
	{
		playAnim(0); // � ����������� �� ������� ������ ��������
		
		return;
	}
	if (H_DXL == 4 && H_DX == 0  ) // ����� �������� ����
	{
		playAnim(1);
		
		return;
	}
	if (H_DX == 1) // �������� ������
	{
		//H_Animation.play(H_MassAnim[0]);
		
		return;
	}
	if (H_DX == 3) // �������� ���� ��� ������
	{
		playAnim(2);
	
		return;
	}
	if (H_DX == 2) // �������� � ����� 
	{
		playAnim(2);
		
		return;
	}
	if (H_DX == 4) // �������� � ����
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
// ���������� ���������� ���� ���� ����� ������� � ������� ����� ����, �� ���� ������� ���
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
	
	
	H_DX = 0; // ���� �� ���� �� ������ �� ������ 0 ������ ����� 
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



/////����������///////
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

///������///
 class Kamera
 {

	 // ����� � ���� ��� ����� 
	 // ���� ����� ������ 
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
	 view.reset(FloatRect(0.0,0.0,window.getSize().x,window.getSize().y)); // ������ �� ������� ����
	 MapRect.height = level.GetMapSize().y*level.GetTileSize().y; MapRect.width= level.GetMapSize().x*level.GetTileSize().x; // ������ � ������� ����� 
	 L_W_H_Size.x = level.GetMapSize().x*level.GetTileSize().x;
	 L_W_H_Size.y = level.GetMapSize().y*level.GetTileSize().y;
	
 }

 inline Kamera::Kamera()
 {

	 
 }
 inline Kamera::~Kamera()
 {
	
 }

 inline void Kamera::updateKamera() // �������� ����� ������, �� ���� �������� �������� �������� ������ �� ������ �� ������, ��������� ��������� ��� ������� ����� � ���� ��� �� ������ ����� ������� �� ������� 

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