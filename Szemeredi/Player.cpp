#include"pch.h"
#include"Player.h"

Player::Player(ChooseAI* ch, ColorAI* c) {
	name = ch->name() + "/" + c->name();
	AI.choose = ch;
	AI.color = c;
}
Player::Player() {
	Player(new RandomChoose(), new RandomColor());
}

uint32_t Player::GetMove(CellPair p, BoardManager& b) {
	if(human)
		std::cout << "\nPlayer " << b.GetPlayer()+1  << " color cell from {"<< p.first + 1 << ", " << p.second + 1 << "}: ";
	return AI.color->GetMove(p, b);
}
CellPair Player::GetMove(BoardManager& b) {
	if(human)
		std::cout << "\nPlayer " << b.NextPlayer()+1  << " choose cells: ";
	return AI.choose->GetMove(b);
}