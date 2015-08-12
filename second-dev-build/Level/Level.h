#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <map>
#include "SFML/Graphics.hpp"
#include "TinyXML/tinyxml.h"
#include <iostream>

namespace lv
{
	struct Object
	{
		int GetPropertyInt(std::string name);
		float GetPropertyFloat(std::string name);
		std::string GetPropertyString(std::string name);
		std::string name;
		std::string type;
		sf::Rect<float> rect;
		std::map<std::string, std::string> properties;
		sf::Sprite sprite;
	};

	struct Layer
	{
		int opacity;
		std::vector<sf::Sprite> tiles;
	};

	class Level
	{
	public:
		bool LoadFromFile(std::string filename);
		Object GetObject(std::string name);
		std::vector<Object> GetObjects(std::string name);
		std::vector<Object> GetAllObjects();
		void Draw(sf::RenderWindow &window);
		sf::Vector2i GetTileSize();
		sf::Vector2i GetMapSize();
		void SetDrawingBounds(sf::FloatRect bounds);
		void DrawWithBBounds(sf::RenderWindow &window);
	private:
		int width, height, tileWidth, tileHeight;
		int firstTileID;
		sf::Rect<float> drawingBounds;
		sf::Texture tilesetImage;
		std::vector<Object> objects;
		std::vector<Layer> layers;
	};
}

#endif //LEVEL_H