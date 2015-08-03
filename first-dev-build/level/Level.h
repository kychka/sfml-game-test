#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml/tinyxml.h"

struct Object
{
	int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);

	std::string name;//Имя
	std::string type;//Тип
	sf::Rect<float> rect;//тип Rect с нецелыми значениями
	std::map<std::string, std::string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый

	sf::Sprite sprite;
};

struct Layer//слои
{
	int opacity;//непрозрачность слоя
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};

class Level//главный класс - уровень
{
public:
	bool LoadFromFile(std::string filename);//возвращает false если не получилось загрузить
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
	void Draw(sf::RenderWindow &window);//рисуем в окно
	sf::Vector2i GetTileSize();//получаем размер тайла
	sf::Vector2i GetMapSize();
	void SetDrawingBounds(sf::FloatRect bounds);
	void DrawWithBBounds(sf::RenderWindow &window);
private:
	int width, height, tileWidth, tileHeight;//Параметры карты
	int firstTileID;//получаем айди первого тайла
	sf::Rect<float> drawingBounds;//размер части карты которую рисуем
	sf::Texture tilesetImage;//текстура карты
	std::vector<Object> objects;//массив типа Объекты
	std::vector<Layer> layers;
};

#endif
