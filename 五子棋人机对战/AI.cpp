#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		std::vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	chess->ChessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{
	int playerNum = 0;//连续棋子
	int aiNum = 0;
	int emptyNum = 0;
	//价值初始化
	/*for (int i = 0; i < scoreMap.size(); i++) {
		std::vector<int> row;
		for (int j = 0; j < scoreMap.size(); j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}*/

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			
			//对每个点进行计算
			if (chess->getChessData(row, col)) continue;
			//九宫格方位
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {

					playerNum = 0;//连续棋子
					aiNum = 0;
					emptyNum = 0;

					if (y == 0 && x == 0) continue; 
					if (y == 0 && x != 1) continue;

					for (int x = -1; x <= 1; x++) {
						if (y == 0 && x == 0) continue;
						//判断五个点
						for (int i = 1; x <= 4; i++) {
							int curRow = row + i * y;
							int curCol = col + i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&&chess->getChessData(curRow,curCol)==1) {
								playerNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}

						//反向
						for (int i = 1; x <= 4; i++) {
							int curRow = row - i * y;
							int curCol = col - i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == 1) {
								playerNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}
						if (playerNum == 1) {
							scoreMap[row][col] += 10;
						}
						else if (playerNum == 2) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 30;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 40;
							}
						}
						else if (playerNum == 3) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 60;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 200;
							}
						}
						else if (playerNum == 4) {
								scoreMap[row][col] += 20000;							
						}

						emptyNum = 0;
						//判断白棋五个点
						for (int i = 1; x <= 4; i++) {
							int curRow = row + i * y;
							int curCol = col + i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == -1) {
								aiNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}

						//反向
						for (int i = 1; x <= 4; i++) {
							int curRow = row - i * y;
							int curCol = col - i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == -1) {
								aiNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
								&& chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}

						if (aiNum == 0) {
							scoreMap[row][col] += 5;
						}
						else if (aiNum == 1) {
							scoreMap[row][col] += 10;
						}
						else if (aiNum == 2) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 25;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 50;
							}
						}
						else if (aiNum == 3) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 55;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 10000;
							}
						}
						else if (aiNum == 4) {
							scoreMap[row][col] += 30000;
						}
					}

				}
			}
		}

		
	}  
}

ChessPos AI::think()
{
	calculateScore();
	std::vector<ChessPos> maxPoints;
	int maxScore = 0;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
