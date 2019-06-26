#include"pch.h"
#include"Board.h"


/*
ChooseAI is used for choosing a pair of free cells from board.
ColorAI is used for colouring one of chosen cells.

To add a new type of strategy it's necessary to add new class that derives from ChooseAI/ColorAI and overrides GetMove function
as well as adding that class to chooseArray/colorArray.
name function is used to easily identify which player won.
*/

class ChooseAI {
public:
	virtual std::string name() = 0;
	virtual CellPair GetMove(Board&) = 0;
};

class ColorAI {
public:
	virtual std::string name() = 0;;
	virtual Cell GetMove(CellPair, Board&) = 0;
};

//
//RANDOM

//Picks pair of cells as well as which to color completely randomly.
class RandomChoose : public ChooseAI {
	[[nodiscard]] std::string name() { return "Random"; };
	[[nodiscard]] CellPair GetMove(Board&) override;
};

class RandomColor : public ColorAI {
	[[nodiscard]] std::string name() { return "Random"; };
	[[nodiscard]] Cell GetMove(CellPair, Board&) override;
};
//

//Colours a cell if it results in win otherwise uses RandomColor's GetMove.
class SlightlyNotRandomColor : public ColorAI {
	[[nodiscard]] std::string name() { return "Slightly Not Random"; };
	[[nodiscard]] Cell GetMove(CellPair, Board&) override;
};

/*
KhanColor/KhanChoose gives a score to each cells then chooses minimum of these scores.

Score is like this:
For each cell P in {1,...,N}, choose all arithmetic sequences that contain P.
For each choosen calculate score is determined by number of cells in this sequence that are coloured in this player's color times some constant + 1.
If sequence contains enemy's colour score is zeroed.

KhanChoose chooses two cells which have smallest score.
KhanColor chooses cell from pair which has smallest score.

*/
class KhanColor : public ColorAI{
	[[nodiscard]] std::string name() { return "Agressive"; };
	[[nodiscard]] Cell GetMove(CellPair, Board&) override;
};

class KhanChoose : public ChooseAI {
	[[nodiscard]] std::string name() { return "Agressive"; };
	[[nodiscard]] CellPair GetMove(Board&) override;
};

/*
SunTzuColor/SunTzuChoose functions the same as KhanColor/KhanChoose if player's colors where swaped when score is calculated.
*/

class SunTzuColor : public ColorAI {
	[[nodiscard]] std::string name() { return "Defensive"; };
	[[nodiscard]] Cell GetMove(CellPair, Board&) override;
};

class SunTzuChoose : public ChooseAI {
	[[nodiscard]] std::string name() { return "Defensive"; };
	[[nodiscard]] CellPair GetMove(Board&) override;
};

class EgoisticalColor : public ColorAI {
	[[nodiscard]] std::string name() { return "Egoistical"; };
	[[nodiscard]] Cell GetMove(CellPair, Board&) override;
};
// chooseArray, coloArray are used for getting data from standard input.

typedef std::shared_ptr<ChooseAI>(*ChooseMake)();
typedef std::shared_ptr<ColorAI>(*ColorMake)();

template <typename T>
[[nodiscard]] constexpr std::shared_ptr<ChooseAI> make() { return std::make_shared<T>(T{}); }
template <typename T>
[[nodiscard]] constexpr std::shared_ptr<ColorAI> make() { return std::make_shared<T>(T{}); }

constexpr std::array<ChooseMake, 3> chooseArray = { make<RandomChoose>, make<KhanChoose>, make<SunTzuChoose> };
constexpr std::array<ColorMake, 3> colorArray = { make<RandomColor>, make<KhanColor>, make<SunTzuColor> };

