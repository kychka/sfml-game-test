#include "Entity.h"

Entity::~Entity(){

}
Entity::Entity(){

	X_Y_Poss.x = NULL;
	X_Y_Poss.y = NULL;
	_frameTime = NULL;
	_Name = "";
}

Entity::Entity(std::string name, Animation animation_mass[], Vector2f position){
	X_Y_Poss = position;
	_Animation.setPosition(X_Y_Poss);
	_Name = name;
	_MassAnim = animation_mass;
}

void Entity::setPossition(float x, float y){
	X_Y_Poss.x = x;
	X_Y_Poss.y = y;
	_Animation.setPosition(X_Y_Poss);
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

void Entity::setAnimation(Animation animation_mass[])
{
	_MassAnim = animation_mass;
}

Vector2f Entity::getCenter()
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

FloatRect Entity::getGlobalBounds(){
	return _Animation.getGlobalBounds();
}

FloatRect Entity::getLocalBounds(){
	return _Animation.getLocalBounds();
}