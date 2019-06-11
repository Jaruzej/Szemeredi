#include"pch.h"



using Cell = uint32_t;
using CellPair = std::pair<Cell, Cell>;
using Board = std::vector<Cell>;

static const std::array<unsigned char, 2> Colors = { 11, 12 }; //Colors for console(players)
static const unsigned char defaultColor = 7;


class BoardManager {
	uint32_t playCounter = 0;
	static const uint32_t startingPlayer = 0;
	uint32_t currentPlayer = startingPlayer;
public:
	Board board;

	uint32_t goal; //How many colors in row are needed to win.

	bool ColorCell(Cell);
	bool ValidMoveAvailable();
	bool ValidateInput(CellPair);
	bool ValidateInput(CellPair, Cell);
	bool WinState();
	bool WinStateIf(Cell, uint32_t);
	std::vector<Cell> GetWinning();


	uint32_t GetCurrentColor();
	uint32_t GetNextColor();
	uint32_t GetPlayer();
	uint32_t NextPlayer();
	void SwitchPlayer();
	Cell& operator[](int);
	size_t size();

	void clear();
};