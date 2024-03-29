#include"pch.h"
#include"Board.h"

bool Board::ValidMoveAvailable() const {
	uint32_t counter = 0;
	for (auto n : this->board)
		counter += (n == defaultColor);
	return (counter >= 2); //At least two cells are available
}

bool Board::ValidateInput(CellPair cells) const {
	return cells.first < board.size() && cells.second < board.size() //Cells chosen are on board
		&& board[cells.first] == defaultColor && board[cells.second] == defaultColor //Cells are not taken already
		&& cells.first != cells.second; //Diffrent cells are chosen
}
bool Board::ValidateInput(CellPair cells, Cell choice) const {
	return cells.first == choice || cells.second == choice;
}

bool Board::WinState() const {
	for(size_t gap = 1; gap <= ceil((float)board.size() / (goal - 1)) - 1; ++gap)
		for (size_t i = 0; i < board.size() - (goal-1)*gap; i++) {
			if (board[i] == defaultColor)
				continue;
			bool flag = true;
			for (size_t j = 1; j < goal; j++)
				if (board[i + j*gap] != board[i])
					flag = false;
			if(flag)
				return true;
		}
	return false;
}
bool Board::WinStateIf(Cell c, uint32_t col) const {
	for (size_t gap = 1; gap <= ceil((float)board.size() / (goal - 1)) - 1; ++gap)
		for (size_t i = 0; i < board.size() - (goal - 1)*gap; i++) {
			uint32_t firstColor = i == c ? col : board[i];
			if (firstColor == defaultColor)
				continue;
			bool flag = true;
			for (size_t j = 1; j < goal; j++)
				if (i+j*gap == c ? col : board[i + j * gap] != firstColor)
					flag = false;
			if (flag)
				return true;
		}
	return false;
}
bool Board::ColorCell(Cell c) {
	if (c >= board.size() || c < 0 || board[c] != defaultColor)
		return false;
	board[c] = GetCurrentColor();
	++playCounter;
	return true;
}

uint32_t Board::GetCurrentColor() const {
	return Colors[currentPlayer];
}

uint32_t Board::GetPlayer() const {
	return currentPlayer;
}

uint32_t Board::NextPlayer() const {
	return (currentPlayer + 1) % Colors.size();
}
void Board::SwitchPlayer() {
	currentPlayer = (currentPlayer + 1) % Colors.size();
}
uint32_t Board::GetNextColor() const {
	return Colors[NextPlayer()];
}

Cell& Board::operator[](int i) {
	return board[i];
}
size_t Board::size() const {
	return board.size();
}

void Board::clear() {
	std::fill_n(board.begin(), board.size(), defaultColor);
	currentPlayer = startingPlayer;
	playCounter = 0;
}

std::vector<Cell> Board::GetWinning() const {
	for (size_t gap = 1; gap <= ceil((float)board.size() / (goal - 1)) - 1; ++gap)
		for (size_t i = 0; i < board.size() - (goal - 1)*gap; i++) {
			if (board[i] == defaultColor)
				continue;
			bool flag = true;
			for (size_t j = 1; j < goal; j++)
				if (board[i + j * gap] != board[i])
					flag = false;
			if (flag) {
				std::vector<Cell> win;
				for (size_t j = 0; j < goal; j++)
					win.push_back(i + j * gap);
				return std::move(win);
			}
			
		}
	return std::vector<Cell>();
}

std::vector<Cell> Board::GetFreeCells() const {
	std::vector<Cell> freeCells;
	for (size_t i = 0; i < size(); ++i)
		if (board[i] == defaultColor)
			freeCells.push_back(i);
	return freeCells;
}