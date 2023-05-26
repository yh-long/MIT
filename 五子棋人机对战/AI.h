#pragma once
#include "Chess.h"
#include <vector>
class AI
{
public:
	void init(Chess *chess);
	void go();
private:
	Chess* chess;
	std::vector<std::vector<int>> scoreMap;
	void calculateScore();
	ChessPos think();
};

