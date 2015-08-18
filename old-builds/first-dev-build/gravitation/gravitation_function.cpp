// Нужно добавлять отдельно в клас врага и игрока.
void Gravitation(float Fy)
	{
		
		for (int i = 0; i<object.size(); i++)
		if (FloatRect(x, y, w, h).intersects(object[i].rect))
		{
			if (object[i].name == "solid") // возможно лучше добавить в карту ground для реализации притяжения
			{	if (Fy>0)	{ y = object[i].rect.top - h; dy = 0; onGround = true; }}
			else 
			 onGround = false;
				dy = dy + 0.001*time; // В классе героя, насколько я понял H_DX вместо dy
		}
	}
