#include "board.h"

Board::Board(unsigned w, unsigned h, std::vector<Cell> _cells)
{
	this->width = w;
	this->height = h;

	this->cells = _cells;
}

unsigned Board::getWidth() { return this-> width; };

unsigned Board::getHeight() { return this-> height; };

int Board::addCell(Cell c)
{
	this->cells.push_back(c);
	return 1;
}

int Board::removeCell(int index)
{
	this->cells.erase(this->cells.begin() + index);
	return 1;
}

int Board::countCells() { return this->cells.size(); };

int Board::getIndexCellByYX(unsigned y, unsigned x)
{
	for (int i = 0; i < this->countCells(); i++)
	{
		if (this->cells[i].getY() == y && this->cells[i].getX() == x)
		{
			return i;
		}
	}
	return EMPTY_CELL;
}

Cell* Board::getCellByIndex(int index) { return &this->cells[index]; };

std::vector<Cell> Board::getCells() { return this->cells; };

void Board::setInvalidCell(std::vector<unsigned> c) {this->invalid.push_back(c);};

std::vector<std::vector<unsigned>> Board::getInvalidCells() { return this->invalid; };
