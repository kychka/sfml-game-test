
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "../level/Level.h"
#include "../audioManager/SoundManager.hpp"
#include "../gravitation/gravitation.h"

am::SoundManager soundManager;

using namespace sf;                        // ������������ ����
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
	void collisionHero(std::vector<Object> &obj);
	void setHeroAnimation(Animation animation_mass[]);
	int getHeroHp();
	int getHeroArm(); 
	Vector2f getHeroPossition(); 
	void updateAndDrawHero(Time &time, std::vector<Object> &obj, RenderWindow &window);
private:
	bool K_ON;                                      // ��������� ��������� ���������� ��� ���( �� ������� ���)
	int H_Hp;                                      // �����
	int H_Arm;                                    // �����
	int H_DX;                                    //������ ��������
	int H_DXL;                                  // ������ ���������� ��������
	float H_Speed;                             // C������� ���������  
	float H_FrameTime;                        // ����� �����  
	void swapHeroAnimation();                 //����� ��������
	int getHeroVectorMove();                 // ������� ������ ��������(���� �� �������� �� �� ����� 0, ���� �������� �� ����� ����� ���������� 1 ���� � ����, 2 ���� � �����, 3 ���� ����, 4 ���� � ����)
	int getHeroVectorMoveLast();            //������ �������� � ��������� ������� ������ ��� ����������� �������� ���� ����� 
	void heroKeyPressed(bool K_ON);
	Vector2f H_X_Y_Poss;                   // ������� �� � � �
	String H_Name;                        // ���
	Animation *H_MassAnim;               // ��������� �� ����� ��������
	AnimatedSprite H_Animation;        // ����� ��������
	Event H_KeyPressedEvent;           // ��� ����������� ��� ������ � �� ������( ����� ��������� ������� �� ����������  ���� ��� ���������� �����������)
	Time time;
};

Hero::Hero()
{
	// ����������� �� ��������� 
	H_Name = "Hero";
	H_Hp = 10;
	H_Arm = 10;
	H_X_Y_Poss.x = NULL;
	H_X_Y_Poss.y = NULL;
	H_DX = NULL;
	H_DXL = NULL;
	H_Speed = 1.0;
	H_FrameTime = NULL;
	K_ON = true;
	
}

Hero::Hero(std::string name, int hp, int arm, Animation  animation_mass[])
{

	H_Name = name;
	H_Hp = hp;
	H_Arm = arm;
	H_MassAnim = animation_mass;

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

void Hero::setHeroPossition(float x, float y)
{
	H_X_Y_Poss.x = x;
	H_X_Y_Poss.y = y;
	H_Animation.setPosition(x, y);
}

inline void Hero::setHeroAnimationSpeed(float as)
{

	H_Animation.setAnimPropers(sf::seconds(as/10), true, false);
	
}

inline void Hero::setHeroSpeed(float hs)
{
	H_Speed = hs/300;
}

inline void Hero::moveHero(float mx, float my)
{
	H_X_Y_Poss.x += mx;
	H_X_Y_Poss.y += my;
	H_Animation.move(mx, my);
}

void Hero::drawHero(RenderWindow &window)
{
	window.draw(H_Animation);

}

inline void Hero::collisionHero(std::vector<Object> &obj)
{
	for (int i = 0; i < obj.size(); i++)
	{   
	
		if (H_Animation.getGlobalBounds().intersects(obj[i].rect))
		{
			
	         // ��� ������ ���� �� ��������, ������ ������
			if (H_DX == 1) { moveHero(0, (H_Speed)*H_FrameTime); }
			if (H_DX == 1) { moveHero((-H_Speed)* H_FrameTime, 0); }
			if (H_DX == 1) { moveHero(0, (-H_Speed)*H_FrameTime); }
			if (H_DX == 1) { moveHero((H_Speed)*H_FrameTime, 0); }
			
			std::cout << "Collision" << std::endl;
		 }
		
	}
}

inline void Hero::setHeroAnimation(Animation animation_mass[])
{
	H_MassAnim = animation_mass;
}


inline void Hero::swapHeroAnimation()
{
 // �������������� �������� �������� �� ����� 

	if (!H_Animation.isPlaying())
	{
		H_Animation.play(H_MassAnim[3]); // �������� �� ������� (���� �� ��������� �� ��� �������� �� ������� ����� ����, ��� ��� �� ����� ����������� ������ � ����� � ������ ��� ������ ������ ���.)
	}


	if (H_DXL == 2 && H_DX == 0 )  // ������ �������� ����
	{
		H_Animation.play(H_MassAnim[1]); // � ����������� �� ������� ������ ��������
		
		return;
	}
	if (H_DXL == 4 && H_DX == 0  ) // ����� �������� ����
	{
		H_Animation.play(H_MassAnim[3]);
		
		return;
	}
	if (H_DX == 1) // �������� ������
	{
		H_Animation.play(H_MassAnim[0]);
		
		return;
	}
	if (H_DX == 3) // �������� ���� ��� ������
	{
		H_Animation.play(H_MassAnim[2]);
	
		return;
	}
	if (H_DX == 2) // �������� � ����� 
	{
		H_Animation.play(H_MassAnim[1]);
		
		return;
	}
	if (H_DX == 4) // �������� � ����
	{
		H_Animation.play(H_MassAnim[3]);
	
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
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		H_DX = 1;
		H_DXL = 1;
		moveHero(0, -H_Speed*time.asMilliseconds());
		return; // ���������������� ������� ��� �� ������, ���� �� ������
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		H_DX = 3;
		H_DXL = 3;
		moveHero(0, H_Speed*time.asMilliseconds());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		H_DX = 2;
		H_DXL = 2;
		moveHero(H_Speed*time.asMilliseconds(), 0);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		H_DX = 4;
		H_DXL = 4;
		moveHero(-H_Speed*time.asMilliseconds(),0);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		soundManager.playRandSound("sword/swipe");
		//////////////////////////////////////////////////////////////////////////////////////
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

void Hero::updateAndDrawHero(Time &time, std::vector<Object> &obj,RenderWindow &window)
{
	this->time = time;
	heroKeyPressed(K_ON);
	swapHeroAnimation();
	drawHero(window);
	H_Animation.updateAnimation(time);
	collisionHero(obj);
	
	// ���� ����� 0 ������ �������� ����������� ��������� ���������� (���� ��� ����� )
	if (H_Hp == 0) 
	{
		K_ON = false;
	}
	
}

Vector2f Hero::getHeroPossition()
{
	return H_X_Y_Poss;
}
