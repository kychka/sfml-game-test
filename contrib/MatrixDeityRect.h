#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

//================================================================================

// Класс-оболочка прямоугольника
// by MatrixDeity
class MatrixDeityRect
{
public:
	MatrixDeityRect(Vector2f& position, Vector2f& size, Color& color); // Конструктор( положение объекта, размер объекта, цвет объекта )
	~MatrixDeityRect(); // Деструктор
	const Vector2f& getSize() const; // Вернет размер объекта
	const Vector2f& getPosition() const; // Вернет координаты объекта
	const Color& getColor() const; // Вернет цвет объекта
	const RectangleShape& getShape() const; // Вернет SFML-фигуру прямоугольник

private:
	RectangleShape rect_; // SFML-прямоугольник
};

