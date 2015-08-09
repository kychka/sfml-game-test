#include"Entity.h"

using namespace sf;

Entity::Entity(){
	X_Y_Poss.x = NULL;
	X_Y_Poss.y = NULL;
	_frameTime = NULL;
}

Entity::Entity(std::string name, float w, float h, Animation animation_mass[]){
	_widht = w;
	_height = h;
	_Name = name;
	_MassAnim = animation_mass;
}

Entity::Entity(){

}

void Entity::setPossition(float x, float y){
	X_Y_Poss.x = x;
	X_Y_Poss.y = y;
}

void Entity::setAnimationSpeed(float as){
	_Animation.setAnimPropers(sf::seconds(as / 10), true, false);
}

void Entity::move(float mx, float  my){
	X_Y_Poss.x += mx;
	X_Y_Poss.y += my;
	_Animation.move(mx, my);
}

void Entity::draw(RenderWindow &window){
	window.draw(_Animation);
}


inline void Entity::setAnimation(Animation animation_mass[])
{
	_MassAnim = animation_mass;
}

inline Vector2f Entity::getCenter()
{
	return Vector2f(_Animation.getGlobalBounds().left + _Animation.getGlobalBounds().height / 2, _Animation.getGlobalBounds().top + _Animation.getGlobalBounds().width / 2);
}

Vector2f Entity::getPossition()
{
	return X_Y_Poss;
}

void Entity::playAnim(int num){
	_Animation.play(_MassAnim[num]);
}

void Entity::setWidht(float w){
	_widht = w;
}

void Entity::setHeight(float h){
	_height = h;
}

float Entity::getWidht(){
	return _widht;
}

float Entity::getHeight(){
	return _height;
}

FloatRect Entity::getRect(){
	return FloatRect(X_Y_Poss.x, X_Y_Poss.y, _widht, _height);
}