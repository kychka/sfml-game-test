#ifndef PAUSE_H
#define PAUSE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "button.h"

using namespace sf;
/*	Меню паузы.
 * Как пользоваться?
 * 1) До main loop'а создать объект класса, передав ссылку на игровое окно
 * 2) В момент, когда игра должна остановиться, просто вызвать функцию exec() и всё :)
 * 3) Остальное класс берёт на себя
 *
 */
class Pause
{
public:
	//Передача ссылки на окно в конструкторе позволяет избавиться от этой необходимости в методах класса
	Pause(RenderWindow &window);
	~Pause();
	void exec(); // Тело паузы
private:
	// Какая кнопка будет выделена?
	enum Button_current{
		resume,
		quit
	};
	void render(); // Вызывается в exec(), потому приватный
	RenderWindow &_window; // Главное окно
	Button _resume; // Кнока возврата
	Button _quit; // Кнопка выхода
	RectangleShape _back; // Задник
	RectangleShape _menu; // Просто синяя полоска
	Event _event; // Главное окно наше, посему мы обрабатываем события
	Button_current _focus_button; // Какая кнопка сейчас выделена?
	View view;// Камера
};

#endif // PAUSE_H
