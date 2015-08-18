#include <SFML/Graphics.hpp>
#include "level.h"
#include <vector>
#include <list>

using namespace sf;

class MapObject
{

public:
	std::vector<Object> obj;//вектор объектов карты
	/*FloatRect getRect()//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	{
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}
	*/
};