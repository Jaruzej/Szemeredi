#include "pch.h"
#include"Game.h"

int main(void) {

	Game G = SetUpGame();

	GameData gd = G.PlayAllGames();

	std::cout << "First player: "  << gd.nameOfPlayer1() << " won " << gd.winsByPlayer1() << " games." << std::endl;
	std::cout << "Second player: " << gd.nameOfPlayer2() << " won " << gd.winsByPlayer2() << " games." << std::endl;
	std::cout << gd.numberOfDraws() << " games were drawn." << std::endl;
	std::cout << "Average game length: " << gd.averageGameLength() << " out of maximum " << G.bm.size()-1;

	return 0;
}
