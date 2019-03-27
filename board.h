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
	std::vector<Cell> invalid;

public:
	Board() {};
	Board(unsigned w, unsigned h, std::vector<Cell> _cells);
	
	unsigned getWidth();
	unsigned getHeight();

	int addCell(Cell);
	int removeCell(int);

	int countCells();
	void setInvalidCell(Cell);

	int getIndexCellByYX(unsigned, unsigned);
	Cell* getCellByIndex(int);
	std::vector<Cell> getCells();
	std::vector<Cell> getInvalidCells();
};

#endif