#pragma once
#include <graphics.h>
#include <vector>
struct ChessPos
{
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {};
};
typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kid_t;

class Chess
{
public:
	Chess(int gradeSize, int marginx, int marginY, float chessSize);
	void init();
	void ChessDown(ChessPos* pos, chess_kid_t val);
	bool clickBoard(int x,int y,ChessPos *pos);
	int getGradeSize();
	int getChessdata(ChessPos* pos);
	int getChessData(int row, int col);	
	bool checkOver();
private:
	IMAGE checkBlackImg;//ºÚÆå
	IMAGE checkWhiteImg;//°×Æå
	int gradeSize;//ÆåÅÌ´óÐ¡
	int margin_x;
	int margin_y;
	float chessSize;
	//Æå×ÓÎ»ÖÃ
	std::vector<std::vector<int>> chessMap;
	//
	bool playerFlag;
	void updateGameMap(ChessPos* pos);
	bool checkWin();
	ChessPos lastPos;
};

