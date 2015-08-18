#include <SFML/Graphics.hpp>
#include "../level/Level.h"
#include "../level/TinyXML/tinyxml.h"

class Gravitation{
public:
	std::vector<Object> object;
	float dx, dy, x, y;
	int w, h;
	bool onGround;
	sf::Sprite sprite;
	float time;
public:
	Gravitation(sf::Sprite sp, Level &lev, float dx, float dy, int W, int H, float X, float Y, float t);
	sf::FloatRect Get_Rect();
	void Collision_With_Map(float Fx, float Fy);
	void update();
};