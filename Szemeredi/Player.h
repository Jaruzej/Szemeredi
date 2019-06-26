#pragma once
#include"pch.h"
#include"AI.h"

/*
Player class is used as a wrapper for ChooseAI's and ColorAI's GetMove function. 
*/
class Player {
public:
	std::string name;
	struct {
		std::shared_ptr<ChooseAI> choose;
		std::shared_ptr<ColorAI> color;
	} AI;

	Cell		GetMove(CellPair, Board&);
	CellPair	GetMove(Board&);
	Player();
	Player(std::shared_ptr<ChooseAI>, std::shared_ptr<ColorAI>);

};

