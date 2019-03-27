//#include "cell.h"
#include "board.h"
#include <array>

#ifndef __ALGO__
#define __ALGO__

#define INVALID_CELL -2
#define WRONG_MOVE -3 

typedef std::pair<int, std::array<unsigned, 2>> CellState;
typedef std::vector<CellState> BoardState;

class Algorithm
{
private:
	Board *board;
	std::vector<Cell> targetCells;
	// state_storage <state <index, <pos_x, pos_y>>>
	std::vector<BoardState> stateStorage;

public:
	Algorithm(Board*);
	std::vector<Cell> getTargetCells();
	BoardState createBoardStateFromBoard(Board);
	Board createBoardFromBoardState(BoardState);

	int manhattanDistance(Cell, Cell);
	int heuristics(std::vector<Cell>);
	int heuristics2(std::vector<Cell>);

	bool isStateExist(Board);

	int moveCell(Cell*, unsigned, unsigned);
	int swapCellsAgressive();

	Board* getCurrentBoard();
	std::vector<BoardState> getStateStorage();
};

#endif