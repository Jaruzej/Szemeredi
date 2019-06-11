#pragma once
#include"pch.h"
#include"AI.h"

class Player {
public:
	bool human = false;
	std::string name;
	struct {
		ChooseAI* choose;
		ColorAI* color;
	} AI;

	Cell		GetMove(CellPair, BoardManager&);
	CellPair	GetMove(BoardManager&);
	Player();
	Player(ChooseAI*, ColorAI*);

};

