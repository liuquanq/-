#include<iostream>

#include "Arraybeta.h"

class Judge
{
public:
	Judge();
	~Judge();

	int Rule_order(int color, int row, char col);//规则判断,color为当前落子颜色
	int Rule_disallowed_moves(Arraybeta a, int row, int col);//禁手规则,返回0表示未违反禁手规则

	//(row,col)表示横纵坐标,count为长度计数,flag为长连方位选择
	int Alive_2(Arraybeta a, int row, int col, char flag, int color);//活二、死二、非二判断
	int Alive_3(Arraybeta a, int row, int col, char flag, int color);//活三、死三、非三判断
	int Alive_4(Arraybeta a, int row, int col, char flag, int color);//活四、死四、非四判断
	int Double_2_judge(Arraybeta a, int row, int col, int color);//双二判断
	int Double_3_judge(Arraybeta a, int row, int col, int color);//双活三禁手
	int Double_4_judge(Arraybeta a, int row, int col, int color);//双四禁手
	int LongConnect_judge(Arraybeta a, int row, int col, int count, char flag);//长连禁手

	int Judgement(Arraybeta a, int row, int col, int color);//判定输赢，平局判定

};