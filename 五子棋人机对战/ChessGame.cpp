#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	man->init(chess);
	ai->init(chess);
}

void ChessGame::play()
{
	chess->init();
	while (true)
	{
		//����
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
		//ai
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
