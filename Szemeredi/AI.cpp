#include"pch.h"
#include"AI.h"

CellPair RandomChoose::GetMove(Board& b) {
	CellPair p;
	p.first = rand() % b.board.size();
	p.second = rand() % b.board.size();
	return p;
}

Cell RandomColor::GetMove(CellPair p, Board& b) {
	return rand() % 2 ? p.first : p.second;
}
Cell SlightlyNotRandomColor::GetMove(CellPair p, Board& b) {
	if (b.WinStateIf(p.first, b.GetCurrentColor()))
		return p.first;
	if (b.WinStateIf(p.second, b.GetCurrentColor()))
		return p.second;
	return rand() % 2 ? p.first : p.second;
}

Cell KhanColor::GetMove(CellPair p, Board& b) {
	std::pair<uint32_t, uint32_t> pairScore = { 0,0 };
	size_t maximum_gap = ceil((float)b.size() / (b.goal - 1)) - 1;
	auto last_possible_index = [&](size_t gap) {return b.size() - (b.goal - 1)*gap; };
	auto point_in_series = [](size_t start, size_t n, size_t gap, size_t cell) {return (start % gap == cell % gap && cell >= start && cell <= start + (n - 1)*gap); };

	if (b.WinStateIf(p.first, b.GetCurrentColor()))
		return p.first;
	if (b.WinStateIf(p.second, b.GetCurrentColor()))
		return p.second;

	for (size_t gap = 1; gap <= maximum_gap; ++gap) {
		for (size_t i = 0; i < last_possible_index(gap); ++i) {
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetNextColor())
					seriesTaken = true;
				if (b[i + j * gap] == b.GetCurrentColor())
					score += 100;
			}
			if (point_in_series(i, b.goal, gap, p.first) && !seriesTaken)
				pairScore.first += score + 1;
			if (point_in_series(i, b.goal, gap, p.second) && !seriesTaken)
				pairScore.second += score + 1;
		}
	}
	if (pairScore.first == pairScore.second)
		return rand() % 2 ? p.first : p.second;
	if (pairScore.first > pairScore.second)
		return p.first;
	return p.second;
}


CellPair KhanChoose::GetMove(Board& b) {
	std::vector<uint32_t> boardScore(b.size(), 0);
	size_t maximum_gap = ceil((float)b.size() / (b.goal - 1)) - 1;
	auto last_possible_index = [&](size_t gap) {return b.size() - (b.goal - 1)*gap; };

	for (size_t gap = 1; gap <= maximum_gap; ++gap) {
		for (size_t i = 0; i < last_possible_index(gap); ++i) {
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetCurrentColor())
					seriesTaken = true;
				if (b[i + j * gap] == b.GetNextColor())
					score += 100;
			}
			if (seriesTaken)
				continue;
			for (size_t j = 0; j < b.goal; ++j)
				boardScore[i + j * gap] += score + 1;
		}
	}

	std::vector<Cell> freeCells = b.GetFreeCells();
	std::pair returnPair = { freeCells[0],freeCells[1] };
	freeCells.erase(std::remove_if(freeCells.begin(), freeCells.end(), [&](Cell c) { return b.WinStateIf(c, b.GetNextColor()) || b[c] != defaultColor; }), freeCells.end());
	if (freeCells.size() <= 2)
		return returnPair;

	auto minIter = std::min_element(freeCells.begin(), freeCells.end(), [&](const Cell& c1, const Cell& c2) {return boardScore[c1] < boardScore[c2]; });
	returnPair.first = *minIter;
	freeCells.erase(minIter);
	minIter = std::min_element(freeCells.begin(), freeCells.end(), [&](const Cell& c1, const Cell& c2) {return boardScore[c1] < boardScore[c2]; });
	returnPair.second = *minIter;
	return returnPair;
}



Cell SunTzuColor::GetMove(CellPair p, Board& b) {
	std::pair<uint32_t, uint32_t> pairScore = { 0,0 };
	size_t maximum_gap = ceil((float)b.size() / (b.goal - 1)) - 1;
	auto last_possible_index = [&](size_t gap) {return b.size() - (b.goal - 1)*gap; };
	auto point_in_series = [](size_t start, size_t n, size_t gap, size_t cell) {return (start % gap == cell % gap && cell >= start && cell <= start + (n - 1)*gap); };

	if (b.WinStateIf(p.first, b.GetCurrentColor()))
		return p.first;
	if (b.WinStateIf(p.second, b.GetCurrentColor()))
		return p.second;

	for (size_t gap = 1; gap <= maximum_gap; ++gap) {
		for (size_t i = 0; i < last_possible_index(gap); ++i) {
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetCurrentColor()) 
					seriesTaken = true;
				if (b[i + j * gap] == b.GetNextColor())
					score += 100;
			}
			if (point_in_series(i,b.goal,gap,p.first) && !seriesTaken)
				pairScore.first += score + 1;
			if (point_in_series(i, b.goal, gap, p.second) && !seriesTaken)
				pairScore.second += score + 1;
		}
	}
	if (pairScore.first == pairScore.second)
		return rand() % 2 ? p.first : p.second;
	if (pairScore.first > pairScore.second)
		return p.first;
	return p.second;
}


CellPair SunTzuChoose::GetMove(Board& b) {
	std::vector<uint32_t> boardScore(b.size(), 0);
	size_t maximum_gap = ceil((float)b.size() / (b.goal - 1)) - 1;
	auto last_possible_index = [&](size_t gap) {return b.size() - (b.goal - 1)*gap; };

	for (size_t gap = 1; gap <= maximum_gap; ++gap) {
		for (size_t i = 0; i < last_possible_index(gap); ++i) {
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetCurrentColor()) 
					seriesTaken = true;
				if (b[i + j * gap] == b.GetNextColor())
					score += 100;
			}
			if (seriesTaken)
				continue;
			for (size_t j = 0; j < b.goal; ++j)
				boardScore[i + j * gap] += score + 1;
		}
	}

	std::vector<Cell> freeCells = b.GetFreeCells();
	std::pair returnPair = { freeCells[0],freeCells[1] };
	freeCells.erase(std::remove_if(freeCells.begin(), freeCells.end(), [&](Cell c) { return b.WinStateIf(c, b.GetNextColor()) || b[c] != defaultColor; }),freeCells.end());
	if (freeCells.size() <= 2)
		return returnPair;

	auto minIter = std::min_element(freeCells.begin(), freeCells.end(), [&](const Cell& c1, const Cell& c2) {return boardScore[c1] < boardScore[c2]; });
	returnPair.first = *minIter;
	freeCells.erase(minIter);
	minIter = std::min_element(freeCells.begin(), freeCells.end(), [&](const Cell& c1, const Cell& c2) {return boardScore[c1] < boardScore[c2]; });
	returnPair.second = *minIter;
	return returnPair;
}

