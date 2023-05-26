#include "Chess.h"
#include <mmsystem.h>
#include <math.h>
#include "tools.h"
#include <conio.h>
#pragma comment(lib,"winmm.lib")
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	for (int i = 0; i < gradeSize; i++) {
		std::vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	//创建游戏窗口
	initgraph(897,895);
	//加载图片
	loadimage(0, "res/棋盘.jpg");

	mciSendString("play res/start.WAV", 0, 0, 0);
	loadimage(&checkBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&checkWhiteImg, "res/white.png", chessSize, chessSize, true);
	//棋盘更新
	for (int i = 0; i < gradeSize; i++) {
		std::vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}	
	}
	playerFlag = true;
}

void Chess::ChessDown(ChessPos* pos, chess_kid_t val)
{
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	if (val == CHESS_BLACK) {
		putimagePNG(x, y, &checkBlackImg);
	}
	else {
		putimagePNG(x, y, &checkWhiteImg);
	}
	updateGameMap(pos);
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	//printf("%d-%d\n", x, y);
	/*if (x - margin_x < margin_x) {
		return false;
	}*/

	int col=(x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize *0.4;	
	int len;
	int ret=false;

	do
	{
		//左上
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
			if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			//printf("%d\n", len);
			break;
		}
		
		//右上
		int rightTopPosX = leftTopPosX+chessSize;
		int rightTopPosY = leftTopPosY;
		len = sqrt((x - rightTopPosX) * (x - rightTopPosX) + (y - rightTopPosY) * (y - rightTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
		
			//printf("%d\n", len);
			break;
		}
		
		//左下
		int leftDownPosX = leftTopPosX;
		int leftDownPosY = leftTopPosY + chessSize;
		len = sqrt((x - leftDownPosX) * (x - leftDownPosX) + (y - leftDownPosY) * (y - leftDownPosY));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		printf("%d\n", len);
		//右下
		int rightDownPosX = leftTopPosX + chessSize;
		int rightDownPosY = leftTopPosY + chessSize;
		len = sqrt((x - rightDownPosX) * (x - rightDownPosX) + (y - rightDownPosY) * (y - rightDownPosY));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		return false;
	} while (true);

	return ret;
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessdata(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin()) {
		if (!playerFlag) {
			mciSendString("play res/不错.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg");
		}else{
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg");
		}
		_getch();
		return true;
	}
	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag=(!playerFlag);
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;
	//水平
	for (int i = 0; i < 5; i++) {
		if (col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4] ){
			return true;
		}
	}
	//垂直
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			chessMap[row-i][col] == chessMap[row-i+1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}
	//"/"
	for (int i = 0; i < 5; i++) {
		if (col - i >= 0 && col + i + 4 < gradeSize &&
			row + i >= 0 && row - i + 4 < gradeSize&&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4] ) {
			return true;
		}
	}
	//"\"
	for (int i = 0; i < 5; i++) {
		if (col - i >= 0 && col - i + 4 < gradeSize &&
			row - i >= 0 && row - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}
	return false;
}
