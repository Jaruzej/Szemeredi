#include"pch.h"
#include"BoardManager.h"

class ChooseAI {
public:
	virtual std::string name() = 0;
	virtual CellPair GetMove(BoardManager&) = 0;
	 const bool human = false;
};

class ColorAI {
public:
	virtual std::string name() = 0;;
	virtual Cell GetMove(CellPair, BoardManager&) = 0;
	 const bool human = false;
};
//HUMAN
class HumanChoose : public ChooseAI {
	std::string name() { return "Gracz"; };
	CellPair GetMove(BoardManager&) override;
	 const bool human = true;
};

class HumanColor : public ColorAI {
	std::string name() { return "Gracz"; };
	Cell GetMove(CellPair, BoardManager&) override;
	 const bool human = true;
};
//
//RANDOM
class RandomChoose : public ChooseAI {
	std::string name() { return "Przypadkowy"; };
	CellPair GetMove(BoardManager&) override;
};

class RandomColor : public ColorAI {
	std::string name() { return "Przypadkowy"; };
	Cell GetMove(CellPair, BoardManager&) override;
};
//
class SligthlyNotRandomColor : public ColorAI {
	Cell GetMove(CellPair, BoardManager&) override;
};

class KhanColor : public ColorAI{
	std::string name() { return "Agresywny"; };
	Cell GetMove(CellPair, BoardManager&) override;
};

class KhanChoose : public ChooseAI {
	std::string name() { return "Agresywny"; };
	CellPair GetMove(BoardManager&) override;
};

class SunTzuColor : public ColorAI {
	std::string name() { return "Defesywny"; };
	Cell GetMove(CellPair, BoardManager&) override;
};

class SunTzuChoose : public ChooseAI {
	std::string name() { return "Defesywny"; };
	CellPair GetMove(BoardManager&) override;
};