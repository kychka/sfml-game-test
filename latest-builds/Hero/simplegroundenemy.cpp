#include "simplegroundenemy.h"

SimpleGroundEnemy::SimpleGroundEnemy(Hero &Her, Kamera &kam) :Enemy(Her,kam)
{
	setAnimationSpeed(0.6f);
	distance = 2000;
}

SimpleGroundEnemy::SimpleGroundEnemy(Hero &her, Kamera &kam, Vector2f position, String name, int hp, int arm, Animation animation_mass[]) : Enemy(her, kam, position, name, hp, arm, animation_mass)
{
	E_DX = NULL;
	E_DXL = NULL;
	E_damage = 5;
	E_HP = hp;
	E_ARM = arm;
	E_Speed = 0.1;
	E_Life = true;
	E_damage = 15;
	_onGround = true;
	IsTarget = false;
	setAnimationSpeed(0.6f);
	distance = 2000;
	TooPointForbaseMove.x = position.x - 100; // размер куда и откуда будет ходить моб// Y воторая позиция по x // можно создать отдельно структуру 
	TooPointForbaseMove.y = position.x + 100; //Нужно это в конструктор
	CurentAnimation = &animation_mass[0];//Во избижание краша 
    BaseVectorMove = E_Speed;
	gravi = 0.5;// В соответствии с выталкиванием в классе родителе 
	texture.loadFromFile("resources/images/bullet.png");
	hero = &her;
	weapon.inicialize(texture, 10, her);
	Vector = 0;
}
SimpleGroundEnemy::~SimpleGroundEnemy()
{

}
void SimpleGroundEnemy::collision(std::vector<lv::Object> &allObj)
{
	Enemy::collision(allObj);
}
int SimpleGroundEnemy::getDamage()
{
	return Enemy::getDamage();
}
bool SimpleGroundEnemy::isAlive()
{
	return Enemy::isAlive();
}
void SimpleGroundEnemy::setDamage(int damage)
{
	Enemy::setDamage(damage);
} 

void SimpleGroundEnemy::collisionWithHero(){
	
	
	if (getGlobalBounds().intersects(targetHero.getGlobalBounds())){
		
		if (targetHero.getDirectory() == 0){         //если игрок идет в лево
			targetHero.setHeroPossition(getPossition().x + getGlobalBounds().width, targetHero.getHeroPossition().y); //отталкиваем его вправо
		}
		if (targetHero.getDirectory() == 1){
			        //если игрок идет вправо
			targetHero.setHeroPossition(getPossition().x - targetHero.getGlobalBounds().width, targetHero.getHeroPossition().y);//отталкиваем его влево
		}
		if (targetHero.getDirectory() == 4){
			//если игрок стоит
			if (getGlobalBounds().left>targetHero.getGlobalBounds().left){
				          //если игрок левее
				targetHero.setHeroPossition(getPossition().x - targetHero.getGlobalBounds().width, targetHero.getHeroPossition().y);//отталкиваем его влево
			}
			if (getGlobalBounds().left<targetHero.getGlobalBounds().left){
				          //если игрок правее
				targetHero.setHeroPossition(getPossition().x + getGlobalBounds().width, targetHero.getHeroPossition().y); //отталкиваем его вправо
			}
		}
		targetHero.takeDamage(getDamage());//игрок получает урон
	}
}

void SimpleGroundEnemy::updateAndDraw(Time &time, std::vector<lv::Object> &allObj, RenderWindow &window){
	this->time = time; 
	//swapAnimation(); Пока не реализованно выключю и добавлю силку на текущюю анимацию и буду её свапать 
	_Animation.play(*CurentAnimation);
    //collisionWithHero();
	
	renderHpBar(E_HP, X_Y_Poss, Vector2f(100, 10), window);
	window.draw(_Animation); 
	_Animation.updateAnimation(time);

	

	moveBase(allObj, window);
	
	GraviUpdate();
	collision(allObj); 

	SeeTargetToo();
	FireTarget();

	// Индекс анимации служит неким таймером для паузы между выстрелами, Vector это направление движения врага служит для определения в дальнейшем полета пули 
	// Буловская переменная IsTarget служит для индикатора выстрела( если в таргете стрельнули а если нет то нет)
	// Все новые данные и методы это временные методы. На ваше усмотрение можете привести их в годное состояние(пока они были созданы дял теста вепона)
	// Мой ии почти не работает. при потере таргета он не может двигатся дальше по совей базовой траектории в методе moveBase()
	// Но так как это прототип для теста не чего страшного 
	// Для определения растояния меду врагом и героем я использую стандартный вектор растояния и высчитываю его(для теста)
	// Тут конечно много каши я на творил и можно запутатся но если возникнут вопросы то пишите.

	weapon.update(window, kamera, allObj, time, *hero, _Animation.getFrameIndex(), Vector, getPossition().x, getPossition().y, IsTarget);
	

	if (E_HP <= 0){
		E_Life = false;
	}
}



bool SimpleGroundEnemy::seeTarget(std::vector<lv::Object> &allObj, RenderWindow &window){//видит ли враг игрока
	
	if (kamera.getVisebleZone().intersects(targetHero.getGlobalBounds())){
		if ((getGlobalBounds().top > targetHero.getGlobalBounds().top + targetHero.getGlobalBounds().height) || (getGlobalBounds().top + getGlobalBounds().height < targetHero.getGlobalBounds().top)){
			//если игрок выше или ниже врага
			return false;
		}
		
			if (getGlobalBounds().left < targetHero.getGlobalBounds().left){//если игрок правее врага
				for (int i = 0; i < allObj.size(); i++){//пробегаемся по вектору обьектов
					if (allObj[i].name == "solid"){//если имя обьекта solid
						if ((getGlobalBounds().left < allObj[i].rect.left) && (allObj[i].rect.left < targetHero.getGlobalBounds().left)){//есть ли между врагом и игроком обьект солид то..
							if (!((getGlobalBounds().top < allObj[i].rect.top) && (targetHero.getGlobalBounds().top < allObj[i].rect.top))){//..проверяем может ли враг заглянуть через него сверху
								if (!((getGlobalBounds().top + getGlobalBounds().height / 2>allObj[i].rect.top + allObj[i].rect.height) && (allObj[i].rect.top + allObj[i].rect.height < targetHero.getGlobalBounds().top + targetHero.getGlobalBounds().height)))
									//может ли враг заглянуть под обьект
									return false;
							}
						}
					}
				}
				//_Animation.setColor(Color::Green);
				return true;
			}
			if (getGlobalBounds().left > targetHero.getGlobalBounds().left){//если игрок левее
				for (int i = 0; i < allObj.size(); i++){
					if (allObj[i].name == "solid"){
						if ((getGlobalBounds().left > allObj[i].rect.left) && (allObj[i].rect.left > targetHero.getGlobalBounds().left)){
							if (!((getGlobalBounds().top < allObj[i].rect.top) && targetHero.getGlobalBounds().top<allObj[i].rect.top))
								if (!((getGlobalBounds().top + getGlobalBounds().height / 2>allObj[i].rect.top + allObj[i].rect.height) && (allObj[i].rect.top + allObj[i].rect.height < targetHero.getGlobalBounds().top + targetHero.getGlobalBounds().height)))
									return false;
						}
					}
				}
				//_Animation.setColor(Color::Green);
				return true;
			}
		}		
}



//Этот блок для теста. Вы можете удалить его или переделать 

void SimpleGroundEnemy::setHp(int hp)
{
	E_HP = hp;
}
int SimpleGroundEnemy::getHp()
{
	return E_HP;
}

void SimpleGroundEnemy::moveBase(std::vector<lv::Object> &allObj, RenderWindow &window)
{

	if (!IsTarget)
	{
		

		if (getPossition().x >= TooPointForbaseMove.y)
		{
			BaseVectorMove = -E_Speed;
			CurentAnimation = &_MassAnim[2];

		}

		if (getPossition().x <= TooPointForbaseMove.x)
		{
			BaseVectorMove = E_Speed;
			CurentAnimation = &_MassAnim[3];

		}

		move(BaseVectorMove*time.asMilliseconds(), 0);
	}
		
}

void SimpleGroundEnemy::GraviUpdate()
{
	move(0, E_Speed*time.asMilliseconds());
}
float SimpleGroundEnemy::getVectorMove()
{
	return BaseVectorMove;
}

bool SimpleGroundEnemy::SeeTargetToo()
{


	std::cout << IsTarget << std::endl;
	float targetDistance = sqrt((hero->getHeroPossition().x - getPossition().x)*(hero->getHeroPossition().x - getPossition().x) +
		(hero->getHeroPossition().y - getPossition().y)*(hero->getHeroPossition().y - getPossition().y));

	if (targetDistance <= 400)
	{
		IsTarget = true;
		return true;
		
	}

	IsTarget = false;
	return  false;
	
}

void SimpleGroundEnemy::FireTarget()
{

	if (IsTarget)
	{
		BaseVectorMove = 0;

		if (hero->getHeroPossition().x <= getPossition().x)
		{
			CurentAnimation = &_MassAnim[1];
			Vector = 1;
		}

		if (hero->getHeroPossition().x > getPossition().x)
		{
			CurentAnimation = &_MassAnim[0];
			Vector = 0;
		}
	}
	
	

}