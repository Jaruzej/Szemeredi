#include"pch.h"
#include"Game.h"
#include<time.h>
bool Game::HumanInGame() {
	for (Player p : players)
		if (p.human)
			return true;
	return false;
}

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

void Game::PlayRound() {
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

}


Game::Game(uint32_t size, uint32_t goal, Player p1, Player p2) {
	bm.goal = goal;
	bm.board.resize(size, defaultColor);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	players = { std::move(p1),std::move(p2) };
}
Player* Game::PlayGame() {
	// Print Player Colors
	if (HumanInGame()) { 
		std::cout << "Player " << bm.GetPlayer() + 1 << " color: ";
		SetConsoleTextAttribute(hConsole, bm.GetCurrentColor());
		std::cout << (unsigned char)219;
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "\n";
		std::cout << "Player " << bm.NextPlayer() + 1 << " color: ";
		SetConsoleTextAttribute(hConsole, Colors[bm.NextPlayer()]);
		std::cout << (unsigned char)219;
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "\n";
	}

	while (bm.ValidMoveAvailable()) {

		if(HumanInGame() || visible)
			std::cout << *this;
		
		PlayRound();
		//std::cin.get();

		if (bm.WinState()) {
			uint32_t player = bm.GetPlayer();
			
			return GetPlayer();
		}
			
	}
	return nullptr;
}

typedef ChooseAI*(*ChooseMake)();
typedef ColorAI*(*ColorMake)();

template <typename T>
ChooseAI* make() { return new T{}; }
template <typename T>
ColorAI* make() { return new T{}; }

std::array<ChooseMake,3> chooseArray = { make<RandomChoose>, make<KhanChoose>, make<SunTzuChoose> };
std::array<ColorMake, 3> colorArray = { make<RandomColor>, make<KhanColor>, make<SunTzuColor> };

std::string typy = " Mo¿liwe typy: \n  Kolorowanie: \n  1. Przypadkowe \n  2. Agresywne \n  3. Defensywne\n";
std::string typy2 = " Mo¿liwe typy: \n  Wybieranie: \n  1. Przypadkowe \n  2. Agresywne \n  3. Defensywne\n";
std::string zle = "Z³y wybór\n";

Player SetUpPlayer() {
	uint64_t type;
	std::cout << typy2;
	std::cin >> type;
	while (!(--type < chooseArray.size() && type >= 0)) {
		std::cout << zle;
		std::cin >> type;
	}
	ChooseAI* choose = chooseArray[type]();
	std::cout << typy;
	std::cin >> type;
	while (!(--type < colorArray.size() && type >= 0)) {
		std::cout << zle;
		std::cin >> type;
	}
	ColorAI* color = colorArray[type]();
	Player p(choose, color);
	return std::move(p);
}

Game SetUpGame() {
	srand(time(NULL));
	setlocale(LC_ALL, "");
	//Plansza
	std::cout << "Wybierz wielkoœæ planszy i d³ugoœæ ci¹gu.\n";
	uint32_t n, k;
	n = k = 0;
	std::cout << "n k: ";
	do {
		std::cin >> n >> k;
	} while (n <= k);
	//Typy komputera
	system("cls");

	std::cout << "Wybierz typy komputera.\n";
	std::cout << "Gracz pierwszy: \n";
	Player p1 = SetUpPlayer();
	std::cout << "Gracz drugi: \n";
	Player p2 = SetUpPlayer();

	system("cls");
	//Iloœæ gier
	uint64_t N;
	std::cout << "Wybierz liczbê rozgrywek.\n";
	std::cin >> N;
	system("cls");
	//Widocznoœæ gry
	std::cout << "Widocznoœæ rozgrywek. (T/N)\n";
	std::string tn;
	std::cin >> tn;
	system("cls");

	Game G(n, k, p1, p2);
	G.numberOfRounds = N;
	G.visible = tn == "T";

	return std::move(G);
}