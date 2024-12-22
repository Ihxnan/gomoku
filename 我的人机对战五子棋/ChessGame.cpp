#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

//开始游戏
void ChessGame::play()
{
	chess->init();
	chess->playerFlag = true;
	while (1)
	{
		// 先由棋手走
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = true;

			continue;
		}
		//由AI走
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = true;

			continue;
		}

	}
}

void ChessGame::play2()
{
	chess->init();
	chess->playerFlag = false;
	while (1)
	{
		//由AI走
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = false;

			continue;
		}
		// 先由棋手走
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = false;

			continue;
		}

	}
}
