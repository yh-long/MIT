#include "Man.h"
#include <Windows.h>
void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;
	
	//判断是否有效
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	//printf("%d %d\n", pos.row, pos.col);
	//落子
	chess->ChessDown(&pos, CHESS_BLACK);
}
