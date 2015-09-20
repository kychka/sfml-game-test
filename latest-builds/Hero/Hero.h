#ifndef HERO_H
#define HERO_H

//#include <vector>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "Entity.h"

using namespace sf;// Пространство имен

class Hero
{
public:
	Hero();
	Hero(std::string name, int hp, int arm, Animation animation_mass[]);
	~Hero();


	void setHeroHp(float hp);
	void setHeroArm(int arm);
	void setHeroPossition(float x, float y);
	void setHeroAnimationSpeed(float as);
	void setHeroSpeed(float hs);
	void setGraviForHero(float g);
	void setHeroAnimation(Animation animation_mass[]);
	void setHeroJump(float j);
	void moveHero(float mx, float  my);
	void drawHero(RenderWindow &window);
	Vector2f getHeroCenter();
	float getHeroHp();
	int getHeroArm();
	Vector2f getHeroPossition();
	void updateAndDrawHero(float frametime, Time &time, std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj, RenderWindow &window);
	void heroControl(std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj, float frametime);
	FloatRect getGlobalBounds();
	int getDirectory();
	void takeDamage(int dam);//функция получения урона
	void immunity(float time);//проверяет включена ли неуязвимость и проверяет время

	///////////////////////////////
	int getFireState();
	int getStayState();
	int getheroAnimIndex();
	void isAmmo_chek(bool is);
	///////////////////////////////

private:
	enum { left, right, up, down, stay } state; ///состояния персонажа. нужно для задавания анимации
	enum { StayLeft, StayRight, } StayState;
	enum { JumpStay, NoJump } JumpState;
	enum { Fire, NoFire }FireState;


	bool isAmmo;

	float H_DistanceForSolid;
	float H_Top1_Rotation;// угол от игрока к вершине 1
	float H_Top2_Rotation;// угол от игрока к вершине 2
	float H_RotationForSolid;
	float H_RotationForHero;
	bool H_GraviForUpdate;
	bool H_Jump;
	void HeroJump(float frametime);                                    // для обсчета прыжка  
	float H_JumpIndex;                                 // для обсчета прыжка
	float H_JumpIndexOld;
	bool H_ColissionFromY;
	bool H_onGround;
	bool K_ON;                                      // Индикатор разрешить управление или нет( по дифолту тру)
	bool isMove;                                    /// для остановки движения
	float H_Hp;                                      // Жизни
	int H_Arm;                                    // Броня
	float H_Gravi;                               // Гравитация
	float H_Speed;                             // Cкорость персонажа  
	float H_FrameTime;                          // Время цикла
	void collisionHeroWithX(std::vector<lv::Object> &objSolid, float frametime);
	void collisionHeroWithY(std::vector<lv::Object> &objSolid, float frametime);
	bool collisionY;
	void updateGravi(float frametime);
	void heroKeyPressed(bool K_ON);
	bool immunityForDamage;
	float immunityTaimer;
	Vector2f H_X_Y_Poss;                   // Позиция по х и у
	String H_Name;                        // Имя
	Animation *H_MassAnim;               // Указатель на силку Анимации
	AnimatedSprite H_Animation;        // Класс анимации
	Event H_KeyPressedEvent;           // Для определения что нажато и не только( можно упростить оставлю на усмотрение  того кто занимается управлением)
	Time time;
	RectangleShape playerHitbox; ///хитбокс персонажа


	// Вершины Героя
	float D_1;
	float D_2;
	float D_3;
	float D_4;
	float C_A1;
	float C_A2;
	float C_A3;
	float C_A4;
	sf::Vector2f A_1;
	sf::Vector2f A_2;
	sf::Vector2f A_3;
	sf::Vector2f A_4;

};
/*grav
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
*///grav

///Камера///
 class Kamera:public Entity
 {

	 // Берет в себя все силки 
	 // Один метод абдейт 
 public:
	 Kamera();
	 Kamera(Hero &hero, lv::Level &level, RenderWindow &window);
	 ~Kamera();
	 Vector2f getPossition();
	 void updateKamera();
	 FloatRect getVisebleZone();
	 Vector2f getSize();
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