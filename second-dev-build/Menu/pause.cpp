﻿#include "pause.h"
Pause::Pause(RenderWindow &window):
	_window(window),
	_resume(L"Продолжить",window.getView().getSize().x/2.5,window.getView().getSize().y/2.5),
	_quit(L"Выйти",window.getView().getSize().x/2.5,window.getView().getSize().y/2.1)
	
{
	_focus_button = resume; // Сперва выделена кнопка возврата
	_back.setFillColor(Color(0,0,0,200));
	_back.setSize(Vector2f(window.getView().getSize().x,window.getView().getSize().y));
	_menu.setSize( Vector2f(window.getView().getSize().x,window.getView().getSize().y/2.5));
	_menu.setPosition(0,window.getView().getSize().y/3);
	_menu.setFillColor(Color(25,40,160,120));
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));// Камера для вида( иначе не видит меню так как в классе игрока тоже есть камера)
}
void Pause::exec(){
	// Цикл выполнения
	
	while(true){ // Пока пауза
		while(_window.pollEvent(_event)){
			if(_event.type == Event::Closed){
				_window.close();
				return;
			}
			if(_event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::F9)) // Хоткей паузы
				return;
			if(_event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down))
				_focus_button = Button_current((_focus_button+1)%2); // % n , где n - количество кнопок
			if(_event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up))
				_focus_button = Button_current((_focus_button == 0) ? 1 : _focus_button-1); // Листание вверх
			if(_event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Return)){ // Если нажата выделенная кнопка
				if(_focus_button == resume) // Если нажата кнопка возврата
					return; // Пауза отжимается
				if(_focus_button == quit){ // Если кнопка выхода
					_window.close(); // Выходим (хорошо бы перед этим вызвать функцию сохранения
					return;
				}

			}

		}
		_window.clear();
		_window.setView(view);
		render();
		_window.display();
	}
}
void Pause::render(){
	_resume.setFocus(false); // Убираем старые выделения
	_quit.setFocus(false);

	if(_focus_button == resume) // И делаем новые
		_resume.setFocus();
	if(_focus_button == quit)
		_quit.setFocus(true);
	_window.draw(_back);
	_window.draw(_menu);
	_resume.render(_window);
	_quit.render(_window);
}
Pause::~Pause()
{

}


