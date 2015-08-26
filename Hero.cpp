#include "Hero.h"

Hero::Hero()
{
	// Конструктор по умолчанию 
	H_Name = "Hero";
	H_Hp = 10;
	H_Arm = 10;
	H_X_Y_Poss.x = NULL;
	H_X_Y_Poss.y = NULL;

	H_Speed = 1.0;
	H_FrameTime = NULL;
	K_ON = true;
	H_onGround = true;
	isMove = false;
	H_JumpIndexOld = NULL;
	H_JumpIndex = H_JumpIndexOld;
	H_Jump = false;
	state = stay;
	H_Gravi = 2.2;
	H_ColissionFromY = true;
	H_GraviForUpdate = true;
	playerHitbox.setSize(Vector2f(189, 245)); /////////////// ТУТ можно подстроить размер хитбокса!!!!
	playerHitbox.setPosition(0, 0);
	playerHitbox.setFillColor(Color::Black); /// это для теста



	A_1.x = playerHitbox.getPosition().x;
	A_1.y = playerHitbox.getPosition().y;
	A_2.x = playerHitbox.getPosition().x + playerHitbox.getSize().y;
	A_2.y = playerHitbox.getPosition().y;
	A_3.x = playerHitbox.getPosition().x + playerHitbox.getSize().x;
	A_3.y = playerHitbox.getPosition().y + playerHitbox.getSize().y;
	A_4.x = playerHitbox.getPosition().x;
	A_4.y = playerHitbox.getPosition().y + playerHitbox.getSize().y;

	D_1 = (atan2(A_1.y - getHeroCenter().y, A_1.x - getHeroCenter().x)) * 180 / 3.14159265;
	D_2 = (atan2(A_2.y - getHeroCenter().y, A_2.x - getHeroCenter().x)) * 180 / 3.14159265;
	D_3 = (atan2(A_3.y - getHeroCenter().y, A_3.x - getHeroCenter().x)) * 180 / 3.14159265;
	D_4 = (atan2(A_4.y - getHeroCenter().y, A_4.x - getHeroCenter().x)) * 180 / 3.14159265;


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
void Hero::setHeroJump(float j)
{
	H_JumpIndexOld = j;
}
void Hero::setGraviForHero(float g)
{
	H_Gravi = g;
}
void Hero::updateGravi(float frametime)
{
	if (H_GraviForUpdate)
	{
		moveHero(0, H_Gravi*H_Speed*frametime);
	}

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
	playerHitbox.setPosition(x, y);
}
void Hero::setHeroAnimationSpeed(float as)
{

	H_Animation.setAnimPropers(sf::seconds(as / 10), true, false);

}
void Hero::setHeroSpeed(float hs)
{
	H_Speed = hs / 300;
}
void Hero::moveHero(float mx, float my)
{
	H_X_Y_Poss.x += mx;
	H_X_Y_Poss.y += my;

	playerHitbox.move(mx, my);
	H_Animation.move(mx, my);
}
void Hero::drawHero(RenderWindow &window)
{
	window.draw(H_Animation);
	// window.draw(playerHitbox);

}
void Hero::collisionHeroWithY(std::vector<lv::Object> &objSolid, float frametime)
{
	for (int i = 0; i < objSolid.size(); i++)
	{
		float SolidCenterX = objSolid[i].rect.left + objSolid[i].rect.width / 2;
		float SolidCenterY = objSolid[i].rect.top; +objSolid[i].rect.height / 2;
		H_RotationForSolid = (atan2(getHeroCenter().y - SolidCenterY, getHeroCenter().x - SolidCenterX)) * 180 / 3.14159265;
		H_Top1_Rotation = (atan2(objSolid[i].Tops.top - getHeroCenter().y, objSolid[i].Tops.left - getHeroCenter().x)) * 180 / 3.14159265;
		H_Top2_Rotation = (atan2(objSolid[i].Tops.height - getHeroCenter().y, objSolid[i].Tops.width - getHeroCenter().x)) * 180 / 3.14159265;

		if (playerHitbox.getGlobalBounds().intersects(objSolid[i].rect))
		{



			if (H_RotationForSolid >= objSolid[i].rotation.left && H_RotationForSolid <= objSolid[i].rotation.top)
			{

				moveHero(0, -H_Gravi*H_Speed*frametime);
				H_onGround = true;
			}
			else
			{
				if (H_Top1_Rotation >= D_3&& H_Top1_Rotation <= D_4)
				{
					moveHero(0, -H_Gravi*H_Speed*frametime);
					H_onGround = true;
					collisionY = true;
				}
				else
				{
					if (H_Top2_Rotation >= D_3&& H_Top2_Rotation <= D_4)
					{
						moveHero(0, -H_Gravi*H_Speed*frametime);
						H_onGround = true;
						collisionY = true;
					}
				}

			}
			if (H_Jump == true)
			{
				H_JumpIndex = 0;
				collisionY = true;
			}


		}
		else { collisionY = false; }


	}
}
void Hero::collisionHeroWithX(std::vector<lv::Object> &objSolid, float frametime)
{
	for (int i = 0; i < objSolid.size(); i++)
	{
		float SolidCenterX = objSolid[i].rect.left + objSolid[i].rect.width / 2;
		float SolidCenterY = objSolid[i].rect.top; +objSolid[i].rect.height / 2;
		H_RotationForSolid = (atan2(getHeroCenter().y - SolidCenterY, getHeroCenter().x - SolidCenterX)) * 180 / 3.14159265;
		H_Top1_Rotation = (atan2(objSolid[i].Tops.top - getHeroCenter().y, objSolid[i].Tops.left - getHeroCenter().x)) * 180 / 3.14159265;
		H_Top2_Rotation = (atan2(objSolid[i].Tops.height - getHeroCenter().y, objSolid[i].Tops.width - getHeroCenter().x)) * 180 / 3.14159265;


		if (playerHitbox.getGlobalBounds().intersects(objSolid[i].rect))
		{
			if (H_Top1_Rotation >= D_3&& H_Top1_Rotation <= D_4)
			{
				continue;
			}

			//Лево
			if (H_RotationForSolid >= objSolid[i].rotation.top && H_RotationForSolid <= 0)
			{

				moveHero(H_Speed*frametime, 0);


			}
			if (H_RotationForSolid >= 0 && H_RotationForSolid <= objSolid[i].rotation.height)
			{

				moveHero(H_Speed*frametime, 0);

			}
			// Право
			if (H_RotationForSolid >= -179.999 && H_RotationForSolid <= objSolid[i].rotation.left)
			{

				moveHero(-H_Speed*frametime, 0);


			}
			if (H_RotationForSolid >= objSolid[i].rotation.width && H_RotationForSolid <= 180)
			{

				moveHero(-H_Speed*frametime, 0);

			}

		}

	}

}
void Hero::setHeroAnimation(Animation animation_mass[])
{
	H_MassAnim = animation_mass;
}
inline Vector2f Hero::getHeroCenter()
{
	return Vector2f(playerHitbox.getGlobalBounds().left + playerHitbox.getGlobalBounds().width / 2, playerHitbox.getGlobalBounds().top + playerHitbox.getGlobalBounds().height / 2);
}
void Hero::heroKeyPressed(bool K_ON)
{
	// Управление персонажем если есть лушче вариант к примеру через кейс, но пока оставлю так

	if (K_ON)
	{
		if (Keyboard::isKeyPressed(Keyboard::Return) && JumpState == NoJump)
		{
			FireState = Fire;
		}
		else { FireState = NoFire; }

		if (Keyboard::isKeyPressed(Keyboard::Space) && (H_onGround))
		{

			JumpState = JumpStay;
			H_onGround = false;
			H_Jump = true;
			return;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			state = right;
			isMove = true;
			StayState = StayRight;
			return;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			state = left;
			isMove = true;
			StayState = StayLeft;
			return;
		}
		isMove = false;
	}
}
int Hero::getHeroHp()
{
	return H_Hp;
}
int Hero::getHeroArm()
{
	return H_Arm;
}
void Hero::updateAndDrawHero(float frametime, Time &time, std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj, RenderWindow &window)
{
	this->time = time;
	H_Animation.updateAnimation(time);
	drawHero(window);
	heroControl(solidObj, groundObj, frametime);
	collisionHeroWithX(solidObj, frametime);
	collisionHeroWithY(solidObj, frametime);
	updateGravi(frametime);



}
/////////////////////
void Hero::heroControl(std::vector<lv::Object> &solidObj, std::vector<lv::Object> &groundObj, float frametime)
{

	heroKeyPressed(K_ON);//функция управления персонажем
	HeroJump(frametime);

	H_Animation.setPosition(getHeroPossition().x, getHeroPossition().y);// из за не пропорционально расположения скарлет в кадре приходится двигать отдельные анимации и возвращять все обратно 


	switch (state)//тут делаются различные действия в зависимости от состояния
	{ //// тут надо разбираться с анимацией
	case left: if (FireState != Fire){ moveHero(-H_Speed*frametime, 0); if (H_onGround == true) { H_Animation.play(H_MassAnim[3]); } }  break;//состояние идти влево
	case right:if (FireState != Fire){ moveHero(H_Speed*frametime, 0); if (H_onGround == true) { H_Animation.play(H_MassAnim[2]); } }break; //состояние идти вправо      
	};
	if (isMove == false && FireState != Fire &&  StayState == StayRight){ H_Animation.play(H_MassAnim[2]); H_Animation.stop(0); } // Пока нету анимаций стоя 

	if (isMove == false && FireState != Fire &&  StayState == StayLeft){ H_Animation.play(H_MassAnim[3]); H_Animation.stop(0); } // Пока нету анимаций стоя 

	if (FireState == Fire && state == left){
		moveHero(-H_Speed*frametime, 0); if (H_onGround == true)
		{
			H_Animation.setPosition(getHeroPossition().x - 81, getHeroPossition().y); H_Animation.play(H_MassAnim[5]);
		}
	}// бегим в лево и стреляем 

	if (FireState == Fire && state == right){
		moveHero(H_Speed*frametime, 0); if (H_onGround == true)
		{
			H_Animation.play(H_MassAnim[4]);
		}
	} // бегим в право и стреляем 

	if (FireState == Fire && isMove == false && StayState == StayLeft)
	{
		H_Animation.setPosition(getHeroPossition().x - 81, getHeroPossition().y); H_Animation.play(H_MassAnim[6]);
	};//стоим в лево и стреляем 

	if (FireState == Fire && isMove == false && StayState == StayRight){ H_Animation.play(H_MassAnim[7]); };// стоим в право и стреляем 

	if (JumpState == JumpStay  && H_onGround == false && StayState == StayLeft){ H_Animation.play(H_MassAnim[3]); }

	if (JumpState == JumpStay  && H_onGround == false && StayState == StayRight){ H_Animation.play(H_MassAnim[2]); }

	if (JumpState == JumpStay  && H_onGround == false && state == right){ H_Animation.play(H_MassAnim[2]); }

	if (isMove == false){ ; state = stay; }

	if (!H_Jump){ JumpState = NoJump; }

}
/////////////////////
void Hero::HeroJump(float frametime)
{

	if (H_Jump == true)
	{
		if (H_JumpIndex <= 1.1)
		{
			H_JumpIndex = H_JumpIndexOld;
			H_Jump = false;
			JumpState = NoJump;
			return;
		}

		moveHero(0, -H_JumpIndex*H_Speed*frametime);
		H_JumpIndex -= 0.1;
		H_onGround = false;
	}


}
Vector2f Hero::getHeroPossition()
{
	return H_X_Y_Poss;
}

FloatRect Hero::getGlobalBounds(){
	std::cout << "Hero.getGlobalBounds()\n";
	return H_Animation.getGlobalBounds();
}

int Hero::getDirectory(){
	return state;
}

void Hero::setColor(Color col){
	H_Animation.setColor(col);
}

/////Гравитация///////
/*grav
Gravi::Gravi()
{
	gravi = NULL;

}
Gravi::Gravi(float gravi)
{
	this->gravi = gravi;
}

Gravi::~Gravi()
{
}

void Gravi::update(Entity &hero, Time &time)
{
	hero.move(0, gravi*time.asMilliseconds());
}
*///grav

///Камера///
Kamera::Kamera(Hero &hero, lv::Level &level, RenderWindow &window)
{
	this->hero = &hero;
	this->level = &level;
	this->window = &window;
	view.reset(FloatRect(0.0, 0.0, window.getSize().x, window.getSize().y)); // камера по размеру окна
	MapRect.height = level.GetMapSize().y*level.GetTileSize().y; MapRect.width = level.GetMapSize().x*level.GetTileSize().x; // данные о размере карты 
	L_W_H_Size.x = level.GetMapSize().x*level.GetTileSize().x;
	L_W_H_Size.y = level.GetMapSize().y*level.GetTileSize().y;
}
Kamera::Kamera()
{
}
Kamera::~Kamera()
{
}
void Kamera::updateKamera() // Получает центр игрока, из него вычетает половину раземера камеры по каждой из сторон, проверяет привишает это размеры карты и если нет то камере можно следить за игроком 
{
	if (hero->getHeroCenter().x - (view.getSize().x / 2) > 0 && hero->getHeroCenter().x + (view.getSize().x / 2) <MapRect.width)
	{
		view.setCenter(hero->getHeroCenter().x, view.getCenter().y);
	}
	if (hero->getHeroCenter().y - (view.getSize().y / 2) > 0 && hero->getHeroCenter().y + (view.getSize().y / 2) < MapRect.height)
	{
		view.setCenter(view.getCenter().x, hero->getHeroCenter().y);
	}
	window->setView(view);
}
Vector2f Kamera::getPossition()
{
	return Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
}