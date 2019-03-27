#include "cell.h"

Cell::Cell(unsigned _y, unsigned _x, Color _c) 
{
	if (_c == Color::WHITE || _c == Color::BLACK)
	{
		this->color = _c;
	}
	this->x = _x;
	this->y = _y;
};

unsigned Cell::getX() { return this->x; }

unsigned Cell::getY() { return this->y; };
	
Color Cell::getColor() { return this->color; };

void Cell::setX(unsigned _x) { this->x = _x; };

void Cell::setY(unsigned _y) { this->y = _y; };
