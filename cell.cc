#include "cell.h"

Cell::Cell(unsigned _y, unsigned _x) 
{
	this->x = _x;
	this->y = _y;
};

unsigned Cell::getX() { return this->x; }

unsigned Cell::getY() { return this->y; };

void Cell::setX(unsigned _x) { this->x = _x; };

void Cell::setY(unsigned _y) { this->y = _y; };
