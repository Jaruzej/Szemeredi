#include"pch.h"
#include"Game.h"
#include<sstream>
#include<time.h>

std::ostream& operator<<(std::ostream& out, Game G) {
	SetConsoleTextAttribute(G.hConsole, 15);
	for (size_t i = 0; i < G.bm.board.size(); i++) {
		uint8_t color = G.bm.board[i];

		std::vector<Cell> winCells = G.bm.GetWinning();
		if (std::find(winCells.begin(),winCells.end(),i)!= winCells.end()) 
			color += 0x7 << 4;
		SetConsoleTextAttribute(G.hConsole, color);
		out << i + 1;
		SetConsoleTextAttribute(G.hConsole, 15);
		out << "|";
	}
	out << "\n";
	
	return out;
}

Cell Game::PlayRound() {
	CellPair cells;
	do {
		cells = GetPlayer()->GetMove(bm);
	} while (!bm.ValidateInput(cells));
	bm.SwitchPlayer();

	uint32_t chosenCell;
	do {
		chosenCell = GetPlayer()->GetMove(cells, bm);
	} while (!bm.ValidateInput(cells,chosenCell));
	bm.ColorCell(chosenCell);

	return chosenCell;
}


Game::Game(uint32_t size, uint32_t goal, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, uint32_t rounds, bool visible) : numberOfGames(rounds), visible(visible) {
	bm.goal = goal;
	bm.board.resize(size, defaultColor);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	players = { p1,p2 };
}
PlayData Game::PlayGame() {
	PlayData pd;
	pd.player1 = players[0];
	pd.player2 = players[1];

	while (bm.ValidMoveAvailable()) {

		if(visible)
			std::cout << *this;
		
		pd.playHistory.push_back(PlayRound());
		//std::cin.get();

		if (bm.WinState()) {
			pd.winner = GetPlayer();
			bm.clear();
			return pd;
		}
			
	}
	bm.clear();
	return pd;
}

GameData Game::PlayAllGames() {
	GameData gd;
	for (size_t i = 0; i < numberOfGames; ++i)
		gd.gameHistory.push_back(PlayGame());
	return gd;
}

std::string GetAllColorTypes() {
	std::stringstream s;
	for (size_t i = 0; i < colorArray.size(); ++i) {
		s << i + 1 << " " << colorArray[i]()->name() << std::endl;
	}
	return s.str();
}
std::string GetAllChooseTypes() {
	std::stringstream s;
	for (size_t i = 0; i < chooseArray.size(); ++i) {
		s << i + 1 << " " << chooseArray[i]()->name() << std::endl;
	}
	return s.str();
}
std::string wrongChoice = "Wrong Choice\n";

Player SetUpPlayer() {
	uint64_t type;
	std::cout << "Available Choose functions: \n";
	std::cout << GetAllChooseTypes();
	std::cin >> type;
	while (!(--type < chooseArray.size() && type >= 0)) {
		std::cout << wrongChoice;
		std::cin >> type;
	}
	std::shared_ptr<ChooseAI> choose = chooseArray[type]();
	
	std::cout << "Available Color functions: \n";
	std::cout << GetAllColorTypes();
	std::cin >> type;
	while (!(--type < colorArray.size() && type >= 0)) {
		std::cout << wrongChoice;
		std::cin >> type;
	}
	std::shared_ptr<ColorAI> color = colorArray[type]();

	Player p(choose, color);
	return p;
}

std::pair<uint32_t, uint32_t> GetBoardSizeFromPlayer() {
	std::cout << "Choose board size and lenght of winning sequence.\n";
	uint32_t n, k;
	n = k = 0;
	std::cout << "n k: ";
	do {
		std::cin >> n >> k;
	} while (n <= k);
	return { n,k };
}

Game SetUpGame() {
	srand(time(NULL));
	setlocale(LC_ALL, "");
	std::pair boardSize = GetBoardSizeFromPlayer();
	system("cls");

	std::cout << "Choose AI types.\n";
	std::cout << "First Player: \n";
	std::shared_ptr<Player> p1 = std::make_shared<Player>(SetUpPlayer());
	std::cout << "Second Player: \n";
	std::shared_ptr<Player> p2 = std::make_shared<Player>(SetUpPlayer());

	system("cls");

	uint64_t N;
	std::cout << "Number of games to play.\n";
	std::cin >> N;
	system("cls");

	std::cout << "Show intermediate steps. (Y/N)\n";
	std::string yn;
	std::cin >> yn;
	system("cls");

	Game G(boardSize.first, boardSize.second, p1, p2, N, yn == "Y" || yn == "y");

	return G;
}



std::ostream& operator<<(std::ostream& out, const PlayData p) {
	out << p.player1->name << "," << p.player2->name << "," << p.winner->name << ",";
	for (auto m : p.playHistory)
		out << m << ",";
	return out;
}


std::ostream& operator<<(std::ostream& out, const GameData g) {
	for (auto play : g.gameHistory)
		out << play << std::endl;
	return out;
}