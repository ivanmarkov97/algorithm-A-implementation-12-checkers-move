#include <iostream>
#include "cell.h"
#include "board.h"
#include "algo.h"

using namespace std;

int main()
{
	vector<Cell> cells;
	Board board = Board(BOARD_H, BOARD_W, cells);

	board.addCell(Cell(0, 0));
	board.addCell(Cell(0, 1));
	board.addCell(Cell(0, 2));
	board.addCell(Cell(0, 3));
	board.addCell(Cell(0, 4));

	board.addCell(Cell(1, 0));
	board.addCell(Cell(1, 1));
	board.addCell(Cell(1, 2));

	board.addCell(Cell(2, 0));
	board.addCell(Cell(2, 1));

	board.addCell(Cell(3, 0));
	board.addCell(Cell(4, 0));

	Cell invalidCell = Cell(4, 3);
	board.setInvalidCell(invalidCell);

	Board initialBoard = board;
	Algorithm algo = Algorithm(&board);

	vector<Cell> currentCells = board.getCells();
	vector<Cell> targetCells = algo.getTargetCells();

	algo.swapCellsAgressive();
	//algo.swapCells();

	return 0;
}