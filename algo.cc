#include "algo.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Algorithm::Algorithm(Board *b)
{
	this->board = b;

	this->targetCells = b->getCells();
	for (int i = 0; i < targetCells.size(); i++)
	{
		targetCells[i].setY(board->getHeight() - targetCells[i].getY() - 1);
		targetCells[i].setX(board->getWidth() - targetCells[i].getX() - 1);
	}

	std::vector<Cell> currentCells = board->getCells();
	BoardState boardState;

	for (int i = 0; i < currentCells.size(); i++)
	{
		std::array<unsigned, 2> cellPos = {currentCells[i].getY(), currentCells[i].getX()};
		std::pair<int, std::array<unsigned, 2>> cellState = {i, cellPos};

		boardState.push_back(cellState);
	}
	stateStorage.push_back(boardState);
}

Board* Algorithm::getCurrentBoard() 
{
	return this->board; 
}

std::vector<BoardState> Algorithm::getStateStorage() 
{
	return this->stateStorage; 
}

BoardState Algorithm::createBoardStateFromBoard(Board b)
{
	std::vector<Cell> currentCells = b.getCells();
	BoardState boardState;

	for (int i = 0; i < currentCells.size(); i++)
	{
		std::array<unsigned, 2> cellPos = {currentCells[i].getY(), currentCells[i].getX()};
		std::pair<int, std::array<unsigned, 2>> cellState = {i, cellPos};

		boardState.push_back(cellState);
	}
	return boardState;
}

Board Algorithm::createBoardFromBoardState(BoardState bs)
{
	std::vector<Cell> cells;
	Board b = Board(BOARD_H, BOARD_W, cells);

	for (int i = 0; i < bs.size(); i++)
	{
		if (bs[i].first != i)
		{
			std::cout << "Alert index wrong position\n";
		}
		else
		{
			unsigned cell_y = bs[i].second[0];
			unsigned cell_x = bs[i].second[1];
			b.addCell(Cell(cell_y, cell_x));
		}
	}
	return b;
}

std::vector<Cell> Algorithm::getTargetCells() 
{
	return this->targetCells; 
}

int Algorithm::manhattanDistance(Cell c1, Cell c2)
{
	return std::abs((int)(c1.getY() - c2.getY())) + std::abs((int)(c1.getX() - c2.getX()));
}

int Algorithm::moveCell(Cell *c, unsigned to_y, unsigned to_x)
{
	std::vector<Cell> invalid = board->getInvalidCells();
	std::vector<Cell> currentCells = board->getCells();

	for (int i = 0; i < invalid.size(); i++)
	{
		if (to_y == invalid[i].getY() && to_x == invalid[i].getX())
		{
			//std::cout << "try to put on invalid place\n";
			return INVALID_CELL;
		}
	}

	for (int i = 0; i < currentCells.size(); i++)
	{
		if (to_y == currentCells[i].getY() && to_x == currentCells[i].getX())
		{
			//std::cout << "you try to put cell on not empty place\n";
			return WRONG_MOVE; 
		}
	}

	if ( (c->getY() - to_y) * (c->getX() - to_x) != 0) // diag
	{
		//std::cout << "diagonal move\n";
		return WRONG_MOVE;
	}
	if (to_y >= board->getHeight() || to_x >= board->getWidth()) // bounds
	{
		return WRONG_MOVE;
	}
	if (to_y < 0 || to_x < 0) // bounds
	{
		return WRONG_MOVE;
	}

	c->setY(to_y);
	c->setX(to_x);

	return 1;
}

int Algorithm::heuristics(std::vector<Cell> currentCells)
{
	const int size = currentCells.size();
	int heuristic = 0;

	for (int i = 0; i < size; i++)
	{
		heuristic += manhattanDistance(currentCells[i], targetCells[i]);
	}
	return heuristic;
}

int Algorithm::heuristics2(std::vector<Cell> currentCells)
{
	const int size = currentCells.size();
	int filledPlaces = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (currentCells[j].getY() == targetCells[i].getY() && 
				currentCells[j].getX() == targetCells[i].getX())
			{
				filledPlaces ++ ;
			}
		}
	}
	return (size - filledPlaces);
}

bool Algorithm::isStateExist(Board b)
{
	int cellMatchedNumber = 0;
	std::vector<Cell> boardCells = b.getCells();

	for (int i = 0; i < stateStorage.size(); i++)
	{
		if (stateStorage[i].size() != boardCells.size())
		{
			std::cout << "size erros. False\n";
			return false;
		}
		for (int j = 0; j < stateStorage[i].size(); j++)
		{
			if (boardCells[j].getY() == stateStorage[i][j].second[0] && 
				boardCells[j].getX() == stateStorage[i][j].second[1])
			{
				cellMatchedNumber ++;
			}
			//std::cout << "index: " << stateStorage[i][j].first << " " << j << " ";
			//std::cout << "position: " << stateStorage[i][j].second[0] << " " << stateStorage[i][j].second[1] << " | ";
			//std::cout << boardCells[j].getY() << " " << boardCells[j].getX() << "\n";
		}
		if (cellMatchedNumber == boardCells.size()) // all
		{
			return true;
		}
		cellMatchedNumber = 0;
	}
	return false;
}


int Algorithm::swapCellsAgressive()
{
	bool addNew = true;
	int stateNum = 0;
	Board currentBoard = createBoardFromBoardState(stateStorage[stateNum]);

	int minCurHeuristic = heuristics2(currentBoard.getCells());

	while(heuristics2(currentBoard.getCells()) != 0)
	{
		for (int i = 0; i < board->getCells().size(); i++)
		{
			for (int _y = 0; _y < board->getHeight(); _y++)
			{
				for (int _x = 0; _x < board->getWidth(); _x++)
				{
					currentBoard = createBoardFromBoardState(stateStorage[stateNum]);
					Cell *c = currentBoard.getCellByIndex(i);
					board = &currentBoard;
					int res = moveCell(c, _y, _x);
					if (res == 1)
					{
						if (!isStateExist(currentBoard) && addNew)
						{
							if (heuristics2(currentBoard.getCells()) <= minCurHeuristic)
							{
								BoardState bs = createBoardStateFromBoard(currentBoard);
								stateStorage.push_back(bs);
								std::cout << "possibleBoards size: " << stateStorage.size();
								std::cout << " " << heuristics2(currentBoard.getCells()) << "\n";

								if (heuristics2(currentBoard.getCells()) < minCurHeuristic)
								{
									stateNum = stateStorage.size() - 1;
								}
								minCurHeuristic = heuristics2(currentBoard.getCells());
							}

							if (heuristics2(currentBoard.getCells()) == 0)
							{
								addNew = false;
								stateNum = stateStorage.size() - 1;
							}
						}	
					}
					//if (res == -2) results[_y][_x] = 'X';
					//if (res == -3) results[_y][_x] = '*';
				}
			}
		}
		if (stateNum < stateStorage.size() - 1)
		{
			stateNum ++ ;
		}
		currentBoard = createBoardFromBoardState(stateStorage[stateNum]);
	}

	std::cout << "SHOW\n";
	char result_board[board->getHeight()][board->getWidth()];
	for (int ii = 0; ii < board->getHeight(); ii++)
		for (int jj = 0; jj < board->getWidth(); jj++)
			result_board[ii][jj] = '*';

	for (int ii = 0; ii < currentBoard.getCells().size(); ii++)
		result_board[currentBoard.getCells()[ii].getY()][currentBoard.getCells()[ii].getX()] = 'O';
	
	for (int ii = 0; ii < board->getHeight(); ii++)
	{
		for (int jj = 0; jj < board->getWidth(); jj++)
		{
			std::cout << result_board[ii][jj] << "\t";
		}
		std::cout << "\n";
	}
}
