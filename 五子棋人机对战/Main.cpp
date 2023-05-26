#include <iostream>
#include "ChessGame.h"

int main() {
	Man man;
	AI ai;
	Chess chess(13,43,43,67.3);
	ChessGame chessgame(&man, &ai, &chess);
	chessgame.play();
	return 0;
}