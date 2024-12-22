#include "Chess.h"
#include <math.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;
    playerFlag = CHESS_BLACK;

    for (int i = 0; i < gradeSize; i++)
    {
        vector<int> row;
        for (int j = 0; j < gradeSize; j++)
        {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}

void Chess::init()
{
    //创建游戏窗口
    initgraph(897, 895);

    //显示棋盘
    loadimage(0, "res/棋盘2.jpg");
    //播放开始提示音
    mciSendString("play res/start.WAV", 0, 0, 0);

    //加载黑棋和白棋的图片
    loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize,true);
    loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize,true);

    //棋盘清零
    for (int i = 0; i < gradeSize; i++)
    {
        for (int j = 0; j < gradeSize; j++)
        {
            chessMap[i][j] = 0;
        }
    }

}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopPosX = margin_x + chessSize * col;
    int leftTopPosY = margin_y + chessSize * row;
    int offset = chessSize * 0.4;

    int len;
    bool ret = false;
    do
    {
        //左上角判断
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset)
        {
            pos->col = col;
            pos->row = row;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }
        //右上角判断
        int x2 = leftTopPosX + chessSize;
        int y2 = leftTopPosY;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->col = col + 1;
            pos->row = row;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //左下角判断
        int x3 = leftTopPosX;
        int y3 = leftTopPosY + chessSize;
        len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
        if (len < offset)
        {
            pos->col = col;
            pos->row = row+1;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //右下角判断
        int x4 = leftTopPosX + chessSize;
        int y4 = leftTopPosY + chessSize;
        len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
        if (len < offset)
        {
            pos->col = col + 1;
            pos->row = row + 1;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

    } while (0);
    
    return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
    PlaySound("res/down8.wav", NULL, SND_ASYNC);
    //mciSendString("play res/down8.wav", 0, 0, 0);
    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

    if (kind == CHESS_WHITE)
    {
        drawPNG(&chessWhiteImg, x, y);
    }
    else
    {
        drawPNG(&chessBlackImg, x, y);
    }
    updateGameMap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
    return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{

    return chessMap[row][col];
}

bool Chess::checkOver()
{
    if (checkWin())
    {
        Sleep(1500);
        if (playerFlag == false)
        {
            //刚才走的是黑棋
            mciSendString("play res/不错.mp3", 0, 0, 0);
            loadimage(0, "res/胜利.jpg");
        }
        else
        {
            mciSendString("play res/失败.mp3", 0, 0, 0);
            loadimage(0, "res/失败.jpg");
        }
        ExMessage msg;
        while (1)
        {
            if (peekmessage(&msg))
            {
                if (msg.message == WM_LBUTTONDOWN)
                    break;
            }

        }
        return true;
    }
    return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
    lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    playerFlag = !playerFlag; // 黑白方交换
}

bool Chess::checkWin()
{
    //最近落子
    int row = lastPos.row;
    int col = lastPos.col;

    //水平方向
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize && chessMap[row][col - i] == chessMap[row][col - i + 1] && chessMap[row][col - i] == chessMap[row][col - i + 2] && chessMap[row][col - i] == chessMap[row][col - i + 3] && chessMap[row][col - i] == chessMap[row][col - i + 4])
        {
            return true;
        }
    }
    //垂直方向
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize && chessMap[row - i][col] == chessMap[row - i + 1][col] && chessMap[row - i][col] == chessMap[row - i + 2][col] && chessMap[row - i][col] == chessMap[row - i + 1][col] && chessMap[row - i][col] == chessMap[row - i + 3][col] && chessMap[row - i][col] == chessMap[row - i + 4][col])
        {
            return true;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (row + i < gradeSize && row + i - 4 >= 0 && col - i >= 0 && col - i + 4 < gradeSize && chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] && chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] && chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] && chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
        {
            return true;
        }
    } 
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize && col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
            chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] && chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] && 
            chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
        {
            return true;
        }
    }
    return false;
}
