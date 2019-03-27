#ifndef __CELL__
#define __CELL__

enum class Color { WHITE, BLACK };

class Cell {
private:
	unsigned x;
	unsigned y;
	Color color;

public:
	Cell(unsigned _x, unsigned _y, Color _c);
	unsigned getX();
	unsigned getY();
	Color getColor();

	void setX(unsigned);
	void setY(unsigned);
};

#endif