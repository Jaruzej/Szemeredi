#pragma once

#include"pch.h"
#include"Player.h"
#include<numeric>

/*
Szemeredi's game is a 2-player colouring game played on a subset of natural numbers {1,...,N}.
Each round first player picks a pair of numbers from the subset, then second player colors one of them in their own color.
Roles are reversed and next round starts.
Game is played until there is a valid move( there are at least two numbers that hasn't been already coloured) or until
there isn't a monochromatic arithmetic sequence of length K.
If there is no valid move, game is drawn.
If there is a winning sequence then player who last coloured wins.

This software is used to test strategies in Computer vs Computer scenarios, which was developed originally for a course 
"Combinatorial Number Theory" at Warsaw University of Technology but it got somewhat expanded later.

More information at https://github.com/Jaruzej/Szemeredi

*/




//PlayData represent an outcome of one game.
class PlayData {
public:
	std::shared_ptr<Player> player1, player2;
	std::shared_ptr<Player> winner;
	std::vector<uint32_t> playHistory;
	friend std::ostream& operator<<(std::ostream&, const PlayData);
};

std::ostream& operator<<(std::ostream&, const PlayData);

//GameData represents outcomes of all games. Class also provides some simple statistics about games.
class GameData {
public:
	std::vector<PlayData> gameHistory;
	std::string nameOfPlayer1() { return gameHistory[0].player1->name; }
	std::string nameOfPlayer2() { return gameHistory[0].player2->name; }
	uint32_t numberOfGames() { return gameHistory.size(); }
	uint32_t numberOfDraws() { return std::count_if(gameHistory.begin(), gameHistory.end(), [](PlayData pd) { return pd.winner == nullptr;    }); };
	uint32_t winsByPlayer1() { return std::count_if(gameHistory.begin(), gameHistory.end(), [](PlayData pd) { return pd.winner == pd.player1; }); };
	uint32_t winsByPlayer2() { return std::count_if(gameHistory.begin(), gameHistory.end(), [](PlayData pd) { return pd.winner == pd.player2; }); };
	std::tuple<uint32_t, uint32_t, uint32_t> winStatistics() { return { winsByPlayer1(),winsByPlayer2(), numberOfDraws()}; }
	uint32_t averageGameLength() { return std::accumulate(gameHistory.begin(), gameHistory.end(), 0, [](uint32_t acc, const PlayData& pd) { return acc + pd.playHistory.size(); })/numberOfGames(); };

	friend std::ostream& operator<<(std::ostream&, const GameData);
};

std::ostream& operator<<(std::ostream&, const GameData);



//Game class holdes data about number of rounds that will be played, who the players are and also handles how the board should be displayed.
//Game class should be constructed through SetUpGame() function.

class Game {
	uint64_t numberOfGames; 
	HANDLE  hConsole; 
	std::array<std::shared_ptr<Player>, 2> players;
	bool visible = false; //Controls whether the game will show all moves.


	[[nodiscard]] std::shared_ptr<Player> GetPlayer() { return players[bm.GetPlayer()]; }
	[[nodiscard]] std::shared_ptr<Player> GetNextPlayer() { return players[bm.NextPlayer()]; }

	//PlayRound gets input from both players( one for choosing cells and one for colouring) checks its validity and switches players.
	Cell PlayRound();
public:
	Game() = delete;
	Game(uint32_t, uint32_t, std::shared_ptr<Player>, std::shared_ptr<Player>, uint32_t, bool);

	Board bm;
	
	//Plays rounds until exit condition given above is met.
	PlayData PlayGame();
	//Plays numberOfGames of games. This should
	GameData PlayAllGames();


	friend std::ostream& operator<<(std::ostream&, const Game);
	
	//Gets all game paramters from standard in.
	friend Game SetUpGame();

};
std::ostream& operator<<(std::ostream&, Game);
[[nodiscard]] Game SetUpGame();


//Functions used in SetUpGame().
[[nodiscard]] std::string GetAllColorTypes();
[[nodiscard]] std::string GetAllChooseTypes();
[[nodiscard]] Player SetUpPlayer();