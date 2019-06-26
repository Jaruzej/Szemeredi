#include"pch.h"
#include"Player.h"

Player::Player(std::shared_ptr<ChooseAI> ch, std::shared_ptr<ColorAI> c) {
	name = ch->name() + "/" + c->name();
	AI.choose = ch;
	AI.color = c;
}
Player::Player() {
	Player(std::make_shared<RandomChoose>(), std::make_shared<RandomColor>());
}

uint32_t Player::GetMove(CellPair p, Board& b) {
	return AI.color->GetMove(p, b);
}
CellPair Player::GetMove(Board& b) {
	return AI.choose->GetMove(b);
}