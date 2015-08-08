#ifndef STARTMENU_H
#define STARTMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "button.h"

using namespace sf;
/* Класс-меню перед началом игры
 * Использование:
 * 1) Создать объект, передав в конструктор главное окно
 * 2) Перед main loop вызвать функцию exec()
 * 3) Profit!
 */
class StartMenu
{
public:
	//Передача ссылки на окно в конструкторе позволяет избавиться от этой необходимости в методах класса
	StartMenu(RenderWindow &window);
	~StartMenu();
	void exec(); // Вызови меня!
private:
	// Какая кнопка будет выделена?
	enum Button_current{
		start,
		setting,
		autors,
		quit
	};
	void render(); // Вызывается в exec(), потому приватный
	RenderWindow &_window; // Главное окно
	Button _start; // Кнока возврата
	Button _settings; // Настройки
	Button _autors; // Титры ( о нас)
	Button _quit; // Кнопка выхода
	RectangleShape _back; // Задник
	RectangleShape _menu; // Просто синяя полоска
	Event _event; // Главное окно наше, посему мы обрабатываем события
	Button_current _focus_button; // Какая кнопка сейчас выделена?
};

#endif // STARTMENU_H
