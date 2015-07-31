#include "hp_bar.h"
void renderHpBar(int hp, Vector2f position, Vector2f size, RenderWindow &window, Color color){
	if(hp < 0 ) // Проверяем входные данные на корректность
		hp = 0; // Не усложняем код обработкой исключений и просто обнуляем hp
	RectangleShape back(size); // Задняя серая полоска
	back.setPosition(position);
	back.setFillColor(Color(50,50,50,128)); // Серый полупрозрачный цвет
	// Сам hp-bar
	RectangleShape bar(Vector2f(size.x*(hp/100.0),size.y)); // Размер умножается на отношение hp к 100,
	//т.е. длина линии пропорционально зависит от хп
	bar.setPosition(position);
	bar.setFillColor(color);
	window.draw(back);
	window.draw(bar);
}
void renderHpBar(int hp, float pos_x, float pos_y, float size_x, float size_y, RenderWindow &window, Color color){
	renderHpBar(hp,Vector2f(pos_x,pos_y),Vector2f(size_x,size_y),window,color);
}
