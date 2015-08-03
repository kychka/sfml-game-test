#include "gravitation.h"

Gravitation::Gravitation(sf::Sprite sp, Level &lev, float dx, float dy, int W, int H, float X, float Y, float t) {
	object = lev.GetAllObjects();
	dx = 0;
	dy = 0;
	sprite = sp;
	time = t;
	w = W; h = H;
	x = X; y = Y;
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

sf::FloatRect Gravitation::Get_Rect()
{
	return sf::FloatRect(x, y, w, h);
}

void Gravitation::Collision_With_Map(float Fx, float Fy)
{
	for (int i = 0; i<object.size(); i++)
	if (Get_Rect().intersects(object[i].rect))
	{
		if (object[i].name == "solid")
		{	if (Fy>0)	
				{ 
				y = object[i].rect.top - h;  
				dy = 0; 
				onGround = true; 
				}
			if (Fy<0)	
				{ 
				y = object[i].rect.top + object[i].rect.height;   
				dy = 0; 
				}
			if (Fx>0)	
				{ 
				x = object[i].rect.left - w;  
				}
			if (Fx<0)	
				{ 
				x = object[i].rect.left + object[i].rect.width; 
				}
		}
		else 
		{ 
			onGround = false;
		}
	}
	if(onGround == false)
		dy = dy + 0.001*time;
}
 
void Gravitation::update()
{
	x += dx*time;
	Collision_With_Map(dx, 0);
	y += dy*time;
	Collision_With_Map(0, dy);
	sprite.setPosition(x+w, y+h);
}