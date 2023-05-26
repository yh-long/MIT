#pragma once
#include"AI.h"
#include "Man.h"
#include "Chess.h"
class ChessGame
{
public:
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();
private:
	Man* man;
	AI* ai;
	Chess* chess;
};

