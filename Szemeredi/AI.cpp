#include"pch.h"
#include"AI.h"

CellPair HumanChoose::GetMove(BoardManager&) {
	CellPair cells;
	std::cin >> cells.first >> cells.second;
	cells.first -= 1;
	cells.second -= 1;

	return cells;
}

Cell HumanColor::GetMove(CellPair, BoardManager&) {
	uint32_t out;
	std::cin >> out;
	out -= 1;
	return out;
}

CellPair RandomChoose::GetMove(BoardManager& b) {
	CellPair p;
	p.first = rand() % b.board.size();
	p.second = rand() % b.board.size();
	return p;
}

Cell RandomColor::GetMove(CellPair p, BoardManager& b) {
	return rand() % 2 ? p.first : p.second;
}
Cell SligthlyNotRandomColor::GetMove(CellPair p, BoardManager& b) {
	if (b.WinStateIf(p.first, b.GetCurrentColor()))
		return p.first;
	if (b.WinStateIf(p.second, b.GetCurrentColor()))
		return p.second;
	return rand() % 2 ? p.first : p.second;
}

Cell KhanColor::GetMove(CellPair p, BoardManager& b) {
	std::pair<uint32_t, uint32_t> pairScore = { 0,0 };
	if (b.WinStateIf(p.first, b.GetCurrentColor()))
		return p.first;
	if (b.WinStateIf(p.second,b.GetCurrentColor()))
		return p.second;
	for (size_t gap = 1; gap <= ceil((float)b.size() / (b.goal - 1)) - 1; ++gap) {
		for (size_t i = 0; i < b.size() - (b.goal - 1)*gap; ++i) {
			if (!((i % gap == p.first % gap && p.first >= i && p.first <= i + (b.goal-1)*gap) || (i % gap == p.second % gap && p.second >= i && p.second <= i + (b.goal - 1)*gap)))
				continue;
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetNextColor()) {
					seriesTaken = true;
					break;
				}
				if (b[i + j * gap] == b.GetCurrentColor())
					score += 1;
			}
			if ((i % gap == p.first % gap && p.first >= i && p.first <= i + (b.goal - 1)*gap) && !seriesTaken)
				pairScore.first += score + 1;
			if((i % gap == p.second % gap && p.second >= i && p.second <= i + (b.goal - 1)*gap) && !seriesTaken)
				pairScore.second += score + 1;
		}
	}
	if (pairScore.first == pairScore.second)
		return rand() % 2 ? p.first : p.second;
	if (pairScore.first > pairScore.second)
		return p.first;
	return p.second;
}


CellPair KhanChoose::GetMove(BoardManager& b) {
	std::vector<uint32_t> boardScore(b.size(),0);
	for (size_t gap = 1; gap <= ceil((float)b.size() / (b.goal - 1)) - 1; ++gap) {
		for (size_t i = 0; i < b.size() - (b.goal - 1)*gap; ++i) {
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetNextColor()) {
					seriesTaken = true;
					break;
				}
				if (b[i + j * gap] == b.GetCurrentColor())
					score += 100;
			}
			if (seriesTaken)
				continue;
			for (size_t j = 0; j < b.goal; ++j) {
				boardScore[i + j * gap] += score + 1;
			}
		}
	}
	for (size_t i = 0; i < boardScore.size(); ++i)
		if (b[i] != defaultColor)
			boardScore[i] = MAXUINT32;
	std::vector<Cell> freeCells;
	for (size_t i = 0; i < b.size(); ++i)
		if (b[i] == defaultColor)
			freeCells.push_back(i);
	if (freeCells.size() == 2)
		return { freeCells[0],freeCells[1] };
	for (size_t i = 0; i < boardScore.size(); ++i)
		if (b.WinStateIf(i, b.GetNextColor()))
			boardScore[i] = MAXUINT32;
	int counter = 0;
	for (size_t i = 0; i < b.size(); ++i)
		if (boardScore[i] != MAXUINT32)
			counter++;
	if (counter < 2)
		return { freeCells[0],freeCells[1] };
	std::pair<uint32_t, uint32_t> retPair;
	auto minIter = std::min_element(boardScore.begin(), boardScore.end());
	retPair.first = std::distance(boardScore.begin(), minIter);
	*minIter = MAXUINT32;
	retPair.second = std::distance(boardScore.begin(), std::min_element(boardScore.begin(), boardScore.end()));
	return retPair;
}



Cell SunTzuColor::GetMove(CellPair p, BoardManager& b) {
	std::pair<uint32_t, uint32_t> pairScore = { 0,0 };
	if (b.WinStateIf(p.first, b.GetCurrentColor()))
		return p.first;
	if (b.WinStateIf(p.second, b.GetCurrentColor()))
		return p.second;
	for (size_t gap = 1; gap <= ceil((float)b.size() / (b.goal - 1)) - 1; ++gap) {
		for (size_t i = 0; i < b.size() - (b.goal - 1)*gap; ++i) {
			if (!((i % gap == p.first % gap && p.first >= i && p.first <= i + (b.goal - 1)*gap) || (i % gap == p.second % gap && p.second >= i && p.second <= i + (b.goal - 1)*gap)))
				continue;
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetCurrentColor()) {
					seriesTaken = true;
					break;
				}
				if (b[i + j * gap] == b.GetNextColor())
					score += 100;
			}
			if ((i % gap == p.first % gap && p.first >= i && p.first <= i + (b.goal - 1)*gap) && !seriesTaken)
				pairScore.first += score + 1;
			if ((i % gap == p.second % gap && p.second >= i && p.second <= i + (b.goal - 1)*gap) && !seriesTaken)
				pairScore.second += score + 1;
		}
	}
	if (pairScore.first == pairScore.second)
		return rand() % 2 ? p.first : p.second;
	if (pairScore.first > pairScore.second)
		return p.first;
	return p.second;
}


CellPair SunTzuChoose::GetMove(BoardManager& b) {
	std::vector<uint32_t> boardScore(b.size(), 0);
	for (size_t gap = 1; gap <= ceil((float)b.size() / (b.goal - 1)) - 1; ++gap) {
		for (size_t i = 0; i < b.size() - (b.goal - 1)*gap; ++i) {
			bool seriesTaken = false;
			uint32_t score = 0;
			for (size_t j = 0; j < b.goal; ++j) {
				if (b[i + j * gap] == b.GetCurrentColor()) {
					seriesTaken = true;
					break;
				}
				if (b[i + j * gap] == b.GetNextColor())
					score += 100;
			}
			if (seriesTaken)
				continue;
			for (size_t j = 0; j < b.goal; ++j) {
				boardScore[i + j * gap] += score + 1;
			}
		}
	}
	for (size_t i = 0; i < boardScore.size(); ++i)
		if (b[i] != defaultColor)
			boardScore[i] = MAXUINT32;
	std::vector<Cell> freeCells;
	for (size_t i = 0; i < b.size(); ++i)
		if (b[i] == defaultColor)
			freeCells.push_back(i);
	if (freeCells.size() == 2)
		return { freeCells[0],freeCells[1] };
	for (size_t i = 0; i < boardScore.size(); ++i)
		if (b.WinStateIf(i, b.GetNextColor()))
			boardScore[i] = MAXUINT32;
	int counter = 0;
	for (size_t i = 0; i < b.size(); ++i)
		if (boardScore[i] != MAXUINT32)
			counter++;
	if (counter < 2)
		return { freeCells[0],freeCells[1] }; 
	std::pair<uint32_t, uint32_t> retPair;
	auto minIter = std::min_element(boardScore.begin(), boardScore.end());
	retPair.first = std::distance(boardScore.begin(), minIter);
	*minIter = _UI32_MAX;
	retPair.second = std::distance(boardScore.begin(), std::min_element(boardScore.begin(), boardScore.end()));
	return retPair;
}