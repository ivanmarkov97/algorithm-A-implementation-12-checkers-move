#include <vector>
#include "cell.h"

#define BOARD_H 8
#define BOARD_W 8

#define EMPTY_CELL -1

#ifndef __BOARD__
#define __BOARD__

class Board {
private:
	unsigned width;
	unsigned height;

	std::vector<Cell> cells;
	std::vector<std::vector<unsigned>> invalid;

public:
	Board() {};
	Board(unsigned w, unsigned h, std::vector<Cell> _cells);
	
	unsigned getWidth();
	unsigned getHeight();

	int addCell(Cell c);
	int removeCell(int index);

	int countCells();
	void setInvalidCell(std::vector<unsigned> c);

	int getIndexCellByYX(unsigned x, unsigned y);
	Cell* getCellByIndex(int index);
	std::vector<Cell> getCells();
	std::vector<std::vector<unsigned>> getInvalidCells();
};

#endif