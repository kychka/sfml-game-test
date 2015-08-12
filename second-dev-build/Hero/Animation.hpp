////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <conio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Level/TinyXML/tinystr.h"
#include "../Level/TinyXML/tinyxml.h"

class Animation
{
public:
	Animation();
	void loadFromXml(std::string adress);//Загрузка из хмл файла 
	void addFrame(sf::IntRect rect);//добавление кадра в ручную 
	void setSpriteSheet(const sf::Texture& texture);//Выбор тайлсета анимации(из которой и будут браться кадры)
	const sf::Texture* getSpriteSheet() const;
	std::size_t getSize() const;
	const sf::IntRect& getFrame(std::size_t n) const;
private:
	std::vector<sf::IntRect> m_frames;
	const sf::Texture* m_texture;
};

#endif // ANIMATION_INCLUDE