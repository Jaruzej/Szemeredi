#pragma once

#include"pch.h"
#include"Player.h"


enum WIN_STATES {PLAYER_1_WIN, PLAYER_2_WIN, DRAW };


class Game {

	Player* GetPlayer() { return &players[bm.GetPlayer()]; }
	Player* GetNextPlayer() { return &players[bm.NextPlayer()]; }
	bool HumanInGame();
	void PlayRound();
public: 
	bool visible = false;
	uint64_t numberOfRounds;

	BoardManager bm;

	HANDLE  hConsole;

	std::array<Player, 2> players;

	Player* PlayGame();
	
	friend std::ostream& operator<<(std::ostream&, Game);

	Game() = delete;
	Game(uint32_t, uint32_t, Player, Player);
};
std::ostream& operator<<(std::ostream&, Game);

Player SetUpPlayer();
Game SetUpGame();