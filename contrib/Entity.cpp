#include"Entity.h"

using namespace sf;

Entity::Entity(){
	_onGround = false;
	_hp = 10;
	_arm = 10;
	X_Y_Poss.x = NULL;
	X_Y_Poss.y = NULL;
	_DX = NULL;
	_DXL = NULL;
	_Speed = 1.0;
	_frameTime = NULL;
	_JumpIndex = 5.0;
	_Jump = NULL;
}

Entity::Entity(std::string name, int hp, int arm, Animation animation_mass[]){
	_Name = name;
	_hp = hp;
	_arm = arm;
	_MassAnim = animation_mass;
}

Entity::Entity(){

}

void Entity::setHp(int hp){
	_hp = hp;
}

void Entity::setArm(int arm){
	_arm = arm;
}

void Entity::setPossition(float x, float y){
	X_Y_Poss.x = x;
	X_Y_Poss.y = y;
}

void Entity::setAnimationSpeed(float as){
	_Animation.setAnimPropers(sf::seconds(as / 10), true, false);
}

void Entity::setSpeed(float hs){
	_Speed = hs / 300;
}

void Entity::move(float mx, float  my){
	X_Y_Poss.x += mx;
	X_Y_Poss.y += my;
	_Animation.move(mx, my);
}

void Entity::draw(RenderWindow &window){
	window.draw(_Animation);
}

inline void Entity::collision(std::vector<lv::Object> &allObj)
{
	for (int i = 0; i < allObj.size(); i++)
	{
		if (allObj[i].name=="ground")
		if (_Animation.getGlobalBounds().intersects(allObj[i].rect))
		{
			_onGround = true;
			move(0, -0.5*time.asMilliseconds());// Отталкиваем от земли 


		}
		if (allObj[i].name == "Solid")
			if (_Animation.getGlobalBounds().intersects(allObj[i].rect))
		{

			if (_DX == 2) { move(-_Speed* time.asMilliseconds(), 0); } // от боковых сторон 
			if (_DX == 4) { move(_Speed *time.asMilliseconds(), 0); }

		}

	}
}

inline void Entity::setAnimation(Animation animation_mass[])
{
	_MassAnim = animation_mass;
}

inline Vector2f Entity::getCenter()
{
	return Vector2f(_Animation.getGlobalBounds().left + _Animation.getGlobalBounds().height / 2, _Animation.getGlobalBounds().top + _Animation.getGlobalBounds().width / 2);
}

inline void Entity::swapAnimation()
{
	// Предпологается загрузка анимаций из файла 

	if (!_Animation.isPlaying())
	{
		_Animation.play(_MassAnim[3]); // Анимация по дефолту (если не выставить то при проверке на колизию будет краш, так как он будет запрашивать данные о кадре а тоесть его позици размер итд.)
	}


	if (_DXL == 2 && _DX == 0)  // Правая анимация стоя
	{
		_Animation.play(_MassAnim[0]); // в зависимости от индеска масива анимаций

		return;
	}
	if (_DXL == 4 && _DX == 0) // Левая анимация стоя
	{
		_Animation.play(_MassAnim[1]);

		return;
	}
	if (_DX == 1) // Анимация прыжка
	{
		//H_Animation.play(H_MassAnim[0]);

		return;
	}
	if (_DX == 3) // Анимация вниз или присел
	{
		_Animation.play(_MassAnim[2]);

		return;
	}
	if (_DX == 2) // Анимация в право 
	{
		_Animation.play(_MassAnim[2]);

		return;
	}
	if (_DX == 4) // Анимация в лево
	{
		_Animation.play(_MassAnim[3]);

		return;
	}

}

inline int Entity::getVectorMove()
{
	return _DX;
}

inline int Entity::getVectorMoveLast()
{
	return _DXL;
}

int Entity::getHp()
{
	return _hp;
}

int Entity::getArm()
{
	return _arm;
}

void Entity::Jump()
{

	if (_onGround == false && _Jump == true)
	{

		move(0, -_Speed*time.asMilliseconds()*_JumpIndex);
		_JumpIndex -= 0.1;

		if (_JumpIndex <= 1)
		{
			_JumpIndex = 5.0;
			_Jump = false;
			return;
		}

	}


}

Vector2f Entity::getPossition()
{
	return X_Y_Poss;
}