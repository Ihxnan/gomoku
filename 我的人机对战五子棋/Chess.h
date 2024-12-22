#pragma once
#include <graphics.h>
#include <vector>
#include "tools.h"

using namespace std;

//��ʾ����λ��
struct ChessPos {
    int row;
    int col;

    ChessPos(int r = 0, int c = 0):row(r),col(c){}
};

typedef enum {
    CHESS_WHITE = -1, //����
    CHESS_BLACK = 1 //����
}chess_kind_t;

class Chess
{
public:
    Chess(int gradeSize, int marginX, int marginY, float chessSize);

    //���̵ĳ�ʼ���� ����ͼƬ��Դ�� ��ʼ���������
    void init();

    //�ж���ָ������λ�ã� �Ƿ�Ϊ��Ч���
    //�����Ч����� ������pos��
    bool clickBoard(int x, int y, ChessPos* pos);

    //��ָ��λ�ã�pos) ���ӣ�kind)
    void chessDown(ChessPos* pos, chess_kind_t kind);

    //��ȡ���̴�С��13��15��19��
    int getGradeSize(); 

    //��ȡָ��λ���Ǻ�����廹�ǿհ�
    int getChessData(ChessPos* pos);
    int getChessData(int row, int col);

    // �������Ƿ����
    bool checkOver(); 

    // ��ʾ���ڸ�˭���壨���ӣ�
    bool playerFlag; //true: �ú����� false: �ð�����

private:
    IMAGE chessBlackImg;//��������
    IMAGE chessWhiteImg;//��������

    int gradeSize; //���̴�С��13��15��17��19��

    int margin_x; //���̵����߽�
    int margin_y; //���̵Ķ����߽�
    float chessSize; //���ӵĴ�С

    //�洢��ǰ��ֵ����ӷֲ����� 0���հ� 1������ -1������
    vector<vector<int>> chessMap;

    void updateGameMap(ChessPos* pos);
    bool checkWin();//�����Ӯ ����Ѿ����� ����true���򷵻�false
    ChessPos lastPos; //�������λ��
};

