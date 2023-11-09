#pragma once

#include <string>
#include<vector>

#define XMAN 700
#define XLAY 750
#define XSTD 780
#define XICE 850

#define XNO 800
#define XB1 810
#define XW0 820

#define XERRO 0
#define NOMINMAX

struct Chess
{
	int color;
	int atkValue;
	int defValue;
	int row;
	int col;
	bool isBoundry;

	Chess() { this->isBoundry = false; };//一般情况下都不是边界，只有在初始赋值的情况下有边界

	Chess(int color, int atkValue, int defValue, int x, int y, bool isBoundry)
	{
		this->color = color;
		this->atkValue = atkValue;
		this->defValue = defValue;
		this->row = x;
		this->col = y;
		this->isBoundry = isBoundry;
	}
	Chess(int color, int atkValue, int defValue)
	{
		this->color = color;
		this->atkValue = atkValue;
		this->defValue = defValue;
		this->isBoundry = false;
	}
	Chess(int color)
	{
		this->color = color;
		this->isBoundry = false;
	}
	Chess(int x, int y)
	{
		this->row = x;
		this->col = y;
		this->isBoundry = false;
	}
	Chess(std::string error)
	{
		this->color = XERRO;
		this->atkValue = XERRO;
		this->defValue = XERRO;
		this->row = XERRO;
		this->col = XERRO;
		this->isBoundry = true;
	}
};

class Map
{
 public:

	Map(void);
	~Map(void);

	Chess getNext(Chess xe, int dir);
	Chess getPrev(Chess xe, int dir);
	Chess getChess(int x, int y);

	int Friend_Color();
	int getSize();
	int getNum();
	int getAtkValue(Chess xe);
	int getDefValue(Chess xe);

	int count_L5(Chess xe);
	int count_A4(Chess xe);
	int count_R4(Chess xe);
	int count_A3(Chess xe);
	int count_S3(Chess xe);
	int count_A2(Chess xe);
	int count_S2(Chess xe);
	int getNum(Chess xe, int dir);

	//L5五连 A4活四 R4冲四 A3活三 S3死三 A2活二 S2死二
	void Map_x_Initialize(int size);
	void numPlus();
	void setAtkValue(Chess xe, int atkValue);
	void setDefValue(Chess xe, int defValue);
	void Friend_Num();
	void Enemy_Num();
	void putAIChess(Map xm, Chess xe);
	void putPlayChess(Chess xe);
	void outputMap();
	void Color_x_Initialize(int color);
	void Friend_x_Enemy();
	void outputChess(Chess xe);
	void outputOneDVector(std::vector<Chess> xe);
	void outputTwoDVector(std::vector<std::vector<Chess>> xe);

 private:

	Chess** map;
	Chess up_Next(Chess xe);
	Chess down_Next(Chess xe);
	Chess left_Next(Chess xe);
	Chess right_Next(Chess xe);
	Chess left_up_Next(Chess xe);
	Chess right_up_Next(Chess xe);
	Chess left_down_Next(Chess xe);
	Chess right_down_Next(Chess xe);
	Chess getErrorChess();

	int size;
	int friendColor;
	int enemyColor;
	int num;

	int getLayNum(Chess xe);
	int getStandNum(Chess xe);
	int getMainNum(Chess xe);
	int getVixeNum(Chess xe);
	int up(Chess xe);
	int down(Chess xe);
	int left(Chess xe);
	int right(Chess xe);
	int left_up(Chess xe);
	int right_up(Chess xe);
	int left_down(Chess xe);
	int right_down(Chess xe);

	int L5(std::vector<std::vector<Chess>> xe, int n);
	int A4(std::vector<std::vector<Chess>> xe, int n);
	int R4(std::vector<std::vector<Chess>> xe, int n);
	int A3(std::vector<std::vector<Chess>> xe, int n);
	int S3(std::vector<std::vector<Chess>> xe, int n);
	int A2(std::vector<std::vector<Chess>> xe, int n);
	int S2(std::vector<std::vector<Chess>> xe, int n);

	int L5(std::vector<Chess> xe, int n);
	int A4(std::vector<Chess> xe, int n);
	int R4(std::vector<Chess> xe, int n);
	int A3(std::vector<Chess> xe, int n);
	int S3(std::vector<Chess> xe, int n);
	int A2(std::vector<Chess> xe, int n);
	int S2(std::vector<Chess> xe, int n);

	int L5(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5);
	int A4(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6);
	int R4(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6);
	int R4(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5);
	int A3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5);
	int A3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6);
	int S3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5);
	int S3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6);
	int S3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6, Chess xe7);
	int A2(Chess xe1, Chess xe2, Chess xe3, Chess xe4);
	int A2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5);
	int A2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6);
	int S2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5);
	int S2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6);

	std::vector<std::vector<Chess>> getChessChain(Chess xe, int n, int loc);
	
	std::vector<Chess> C4(Chess xe, int dir, int loc);
	std::vector<Chess> C5(Chess xe, int dir, int loc);
	std::vector<Chess> C6(Chess xe, int dir, int loc);
	std::vector<Chess> C7(Chess xe, int dir, int loc);
	std::vector<Chess> D1(Chess xe, int n, int dir);
	std::vector<Chess> D2(Chess xe, int n, int dir);
	std::vector<Chess> D3(Chess xe, int n, int dir);
	std::vector<Chess> D4(Chess xe, int n, int dir);
	std::vector<Chess> D5(Chess xe, int n, int dir);
	std::vector<Chess> D6(Chess xe, int n, int dir);
	std::vector<Chess> D7(Chess xe, int n, int dir);

	std::string define_string(int code);
	std::string bool_string(bool flag);

	bool XB1_x_OK(std::vector<Chess> xe);
	bool Chain_x_OK(std::vector<std::vector<Chess>> vxe);

};


