
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "Level\Level.h"
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


Hero::Hero()
{
	// Конструктор по умолчанию 
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
	H_onGround = false;
	H_JumpIndex = 5.0;
	H_Jump = false;
	
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

inline void Hero::collisionHero(std::vector<lv::Object> &objSolid, std::vector<lv::Object> &objGround)
{
	for (int i = 0; i < objGround.size(); i++)
	{   
	
		if (H_Animation.getGlobalBounds().intersects(objGround[i].rect))
		{
			 H_onGround = true;
			 moveHero(0, -0.5*time.asMilliseconds());// Отталкиваем от земли 
			
			
		 }

		
	}
	for (int i = 0; i < objSolid.size();i++)
	{
	
		if (H_Animation.getGlobalBounds().intersects(objSolid[i].rect))
		{
			
			if (H_DX == 2) { moveHero(-H_Speed* time.asMilliseconds(), 0); } // от боковых сторон 
			if (H_DX == 4) { moveHero(H_Speed *time.asMilliseconds(), 0); }
			
		}
		
	}


}


inline void Hero::setHeroAnimation(Animation animation_mass[])
{
	H_MassAnim = animation_mass;
}

inline Vector2f Hero::getHeroCenter()
{
	return Vector2f(H_Animation.getGlobalBounds().left+H_Animation.getGlobalBounds().height/2, H_Animation.getGlobalBounds().top+ H_Animation.getGlobalBounds().width/2);
}


inline void Hero::swapHeroAnimation()
{
 // Предпологается загрузка анимаций из файла 

	if (!H_Animation.isPlaying())
	{
		H_Animation.play(H_MassAnim[3]); // Анимация по дефолту (если не выставить то при проверке на колизию будет краш, так как он будет запрашивать данные о кадре а тоесть его позици размер итд.)
	}


	if (H_DXL == 2 && H_DX == 0 )  // Правая анимация стоя
	{
		H_Animation.play(H_MassAnim[0]); // в зависимости от индеска масива анимаций
		
		return;
	}
	if (H_DXL == 4 && H_DX == 0  ) // Левая анимация стоя
	{
		H_Animation.play(H_MassAnim[1]);
		
		return;
	}
	if (H_DX == 1) // Анимация прыжка
	{
		//H_Animation.play(H_MassAnim[0]);
		
		return;
	}
	if (H_DX == 3) // Анимация вниз или присел
	{
		H_Animation.play(H_MassAnim[2]);
	
		return;
	}
	if (H_DX == 2) // Анимация в право 
	{
		H_Animation.play(H_MassAnim[2]);
		
		return;
	}
	if (H_DX == 4) // Анимация в лево
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
// Управление персонажем если есть лушче вариант к примеру через кейс, но пока оставлю так
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
	
	
	H_DX = 0; // если не чего не нажали то вектор 0 тоесть стоим 
}



int Hero::getHeroHp()
{
	return H_Hp;
}

int Hero::getHeroArm()
{
	return H_Arm;
}

void Hero::updateAndDrawHero(Time &time, std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj,RenderWindow &window)
{
	this->time = time;
	heroKeyPressed(K_ON);
	swapHeroAnimation();
	drawHero(window);
	HeroJump();
	H_Animation.updateAnimation(time);
	collisionHero(solidObj, groundObj);
	

	
	if (H_Hp == 0) 
	{
		K_ON = false;
	}
	
}

void Hero::HeroJump()
{
	
	if (H_onGround == false && H_Jump == true)
	{
		
		moveHero(0, -H_Speed*time.asMilliseconds()*H_JumpIndex);
		H_JumpIndex -= 0.1;

		if (H_JumpIndex <=1)
		{
			H_JumpIndex = 5.0;
			H_Jump = false;
			return;
		}
		
	}
	 
   
}

Vector2f Hero::getHeroPossition()
{
	return H_X_Y_Poss;
}

/////Гравитация///////
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
	 hero.moveHero(0, gravi*time.asMilliseconds());

 }

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
 
 

 inline Kamera::Kamera(Hero &hero, lv::Level &level, RenderWindow &window) 
 {
	 this->hero = &hero;
	 this->level = &level;
	 this->window = &window;
	 view.reset(FloatRect(0.0,0.0,window.getSize().x,window.getSize().y)); // камера по размеру окна
	 MapRect.height = level.GetMapSize().y*level.GetTileSize().y; MapRect.width= level.GetMapSize().x*level.GetTileSize().x; // данные о размере карты 
	 L_W_H_Size.x = level.GetMapSize().x*level.GetTileSize().x;
	 L_W_H_Size.y = level.GetMapSize().y*level.GetTileSize().y;
	
 }

 inline Kamera::Kamera()
 {

	 
 }
 inline Kamera::~Kamera()
 {
	
 }

 inline void Kamera::updateKamera() // Получает центр игрока, из него вычетает половину раземера камеры по каждой из сторон, проверяет привишает это размеры карты и если нет то камере можно следить за игроком 

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
 inline Vector2f Kamera::getPossition()
 {

	 return Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
 }
