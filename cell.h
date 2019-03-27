#ifndef __CELL__
#define __CELL__

class Cell {
private:
	unsigned x;
	unsigned y;

public:
	Cell(unsigned, unsigned);
	unsigned getX();
	unsigned getY();

	void setX(unsigned);
	void setY(unsigned);
};

#endif