#include"pch.h"



using Cell = uint32_t; //Cell represents a number on a board
using CellPair = std::pair<Cell, Cell>; 
using PlayingArea = std::vector<Cell>;

constexpr std::array<unsigned char, 2> Colors = { 11, 12 }; //Colors for console(players)
constexpr unsigned char defaultColor = 7; //White console color

//Board is used to keep track of a game and provide functions that can tell something about state of a game such as getting all cells which hasn't been taken yet.

class Board {
	uint32_t playCounter = 0;
	static const uint32_t startingPlayer = 1;
	uint32_t currentPlayer = startingPlayer;
public:
	PlayingArea board;

	uint32_t goal; //How many colors in row are needed to win.

	bool ColorCell(Cell);
	[[nodiscard]] bool ValidMoveAvailable() const;
	[[nodiscard]] bool ValidateInput(CellPair) const; //Checks if both of cells from CellPair are in {1,...,N} and uncoloured.
	[[nodiscard]] bool ValidateInput(CellPair, Cell) const; //Checks if CellPair constains Cell.
	[[nodiscard]] bool WinState() const; //Checks if there is a monochromatic arithmetic sequence of length "goal".
	[[nodiscard]] bool WinStateIf(Cell, uint32_t) const; //Checks what would WinState() return if given cell was coloured in given colour. 
	[[nodiscard]] std::vector<Cell> GetWinning() const; //Returns sequence which is monochromatic arithmetic sequence of length "goal".
	[[nodiscard]] std::vector<Cell> GetFreeCells() const; //Return all non-coloured cells.

	[[nodiscard]] uint32_t GetCurrentColor() const; //Color of current player.
	[[nodiscard]] uint32_t GetNextColor() const; //Color of next player.
	[[nodiscard]] uint32_t GetPlayer() const; //Returns id of current player (0 or 1)
	[[nodiscard]] uint32_t NextPlayer() const;

	void SwitchPlayer();

	[[nodiscard]] Cell& operator[](int);
	[[nodiscard]] size_t size() const;

	void clear();
};