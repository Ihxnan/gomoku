#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

//��ʼ��Ϸ
void ChessGame::play()
{
	chess->init();
	chess->playerFlag = true;
	while (1)
	{
		// ����������
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = true;

			continue;
		}
		//��AI��
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
		//��AI��
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = false;

			continue;
		}
		// ����������
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			chess->playerFlag = false;

			continue;
		}

	}
}
