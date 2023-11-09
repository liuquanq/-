#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include "Map.h"
#include <Windows.h>

#define Va1 67108864
#define Va2 67000000
#define Va3 8388608
#define Va4 4194304
#define Va5 2097152
#define Va6 1048576
#define Va7 524288
#define Va8 262144
#define Va9 131072
#define Va10 65536
#define Va11 32768
#define Va12 16384
#define Va13 8192
#define Va14 4096
#define Va15 2048

class Robot
{
 public:

	Robot(void);
	~Robot(void);

	int AI(Map xm,int color,int order);
	int getInput();
	int Input_x_OK(Map xm, Chess xe);
	int WinnerCheck(Map xm); 

	void Atk_x_Def(Map xm);

 private:

	Chess getBestChess(Map xm);

	int Random_location(int n);
	int getAtkValue(Map xm, Chess xe);
	int getDefValue(Map xm, Chess xe);
	int Forbidden_move(int Chess_value[]);

	void giveChess_value(Map xm);
	void putChess(Map xm, Chess xe);
	void putChessman(Map xm, Chess xe);

};

