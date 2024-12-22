#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"ChessGame.h"
#include<time.h>


int main()
{
    srand((unsigned int)time(NULL));
    Man man;
    Chess chess(13, 44, 43, 67.3);
    AI ai;
    ChessGame game(&man, &ai, &chess);

    game.play2();

    return 0;
}