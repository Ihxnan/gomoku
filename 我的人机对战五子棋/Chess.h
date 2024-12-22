#pragma once
#include <graphics.h>
#include <vector>
#include "tools.h"

using namespace std;

//表示落子位置
struct ChessPos {
    int row;
    int col;

    ChessPos(int r = 0, int c = 0):row(r),col(c){}
};

typedef enum {
    CHESS_WHITE = -1, //白棋
    CHESS_BLACK = 1 //黑棋
}chess_kind_t;

class Chess
{
public:
    Chess(int gradeSize, int marginX, int marginY, float chessSize);

    //棋盘的初始化： 加载图片资源， 初始化相关数据
    void init();

    //判断在指定坐标位置， 是否为有效点击
    //如果有效点击， 保存在pos中
    bool clickBoard(int x, int y, ChessPos* pos);

    //在指定位置（pos) 落子（kind)
    void chessDown(ChessPos* pos, chess_kind_t kind);

    //获取棋盘大小（13，15，19）
    int getGradeSize(); 

    //获取指定位置是黑棋白棋还是空白
    int getChessData(ChessPos* pos);
    int getChessData(int row, int col);

    // 检查棋局是否结束
    bool checkOver(); 

    // 表示现在该谁下棋（落子）
    bool playerFlag; //true: 该黑子走 false: 该白棋走

private:
    IMAGE chessBlackImg;//黑棋棋子
    IMAGE chessWhiteImg;//白棋棋子

    int gradeSize; //棋盘大小（13，15，17，19）

    int margin_x; //棋盘的左侧边界
    int margin_y; //棋盘的顶部边界
    float chessSize; //棋子的大小

    //存储当前棋局的棋子分布数据 0：空白 1：黑子 -1：白子
    vector<vector<int>> chessMap;

    void updateGameMap(ChessPos* pos);
    bool checkWin();//检查输赢 如果已经结束 返回true否则返回false
    ChessPos lastPos; //最后落子位置
};

