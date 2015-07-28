#include "MatrixDeityRect.h"

MatrixDeityRect::MatrixDeityRect(Vector2f& position, Vector2f& size, Color& color)
{
	rect_.setPosition(position);
	rect_.setSize(size);
	rect_.setFillColor(color);
}

//================================================================================

MatrixDeityRect::~MatrixDeityRect()
{
}

//================================================================================

const Vector2f& MatrixDeityRect::getSize() const
{
	return rect_.getSize();
}

//================================================================================

const Vector2f& MatrixDeityRect::getPosition() const
{
	return rect_.getPosition();
}

//================================================================================

const Color& MatrixDeityRect::getColor() const
{
	return rect_.getFillColor();
}

//================================================================================

const RectangleShape& MatrixDeityRect::getShape() const
{
	return rect_;
}