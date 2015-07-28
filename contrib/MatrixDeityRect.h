#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

//================================================================================

// Shell of rectangle
// by MatrixDeity
class MatrixDeityRect
{
public:
	MatrixDeityRect(Vector2f& position, Vector2f& size, Color& color); // Constructor
	~MatrixDeityRect(); // Destructor
	const Vector2f& getSize() const; // Return object size
	const Vector2f& getPosition() const; // Return object position
	const Color& getColor() const; // Return object color
	const RectangleShape& getShape() const; // Return SFML-shape rectangle

private:
	RectangleShape rect_; // SFML-rectangle
};

