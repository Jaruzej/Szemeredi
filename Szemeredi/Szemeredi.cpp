#include "pch.h"
#include"Game.h"
#include"Player.h"

#include<time.h>
int main(void) {
	Game G = SetUpGame();

	std::array<uint64_t, 3> wins = { 0 };
	for (size_t i = 0; i < G.numberOfRounds; ++i) {
		Player* p = G.PlayGame();
		if (p != nullptr) {
			if (G.visible) {
				SetConsoleTextAttribute(G.hConsole, Colors[G.bm.GetPlayer()]);
				std::cout << "Gracz " << p->name;
				SetConsoleTextAttribute(G.hConsole, 7);
				std::cout << " wygra³. \nStan rozgrywki:" << G;
			}
			if (p == &G.players[0])
				wins[0] += 1;
			else
				wins[1] += 1;
		}
		else {
			if (G.visible)
				std::cout << "Remis. \nStan rozgrywki:" << G;
			wins[2] += 1;
		}
			
		G.bm.clear();
	}

	std::cout << "\n\nStan koñcowy\n(wygrane przez gracza '" << G.players[0].name << "'/remis/wygrane przez gracza '" << G.players[1].name << "'): \n" << wins[0] << "/" << wins[2] << "/" << wins[1];



	std::cin.get();
	std::cin.get();

	return 0;
}
