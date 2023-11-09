#include "Robot.h"
#include "Map.h"
#include "Draw.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>

Robot::Robot(void)
{
}

Robot::~Robot(void)
{
}

Chess Robot::getBestChess(Map xm)
{
	using std::vector;
	vector<Chess> chessChain;

	for (int i = 1; i <= xm.getSize(); i++)
	{
		for (int j = 1; j <= xm.getSize(); j++)
		{
			if (xm.getChess(i, j).color == XNO)
			{
				chessChain.push_back(xm.getChess(i, j));
			}
		}

	}
	Chess maxAtk;
	Chess maxDef;
	vector<Chess>::iterator it;
	int countNone = 0;
	int countLen = 0;


	it = chessChain.begin();
	maxAtk = *it;
	maxDef = *it;
	while (it != chessChain.end())
	{
		if ((*it).atkValue > maxAtk.atkValue) maxAtk = *it;
		if ((*it).defValue > maxDef.defValue) maxDef = *it;
		it++;
	}//将找最大和找最小合并，减少判断时间

	vector<Chess> secondWeight;//如果maxDef>maxAtk，存maxDef;反之亦然
	int flag = 0;//记录是maxAtk大还是maxDef大
	if (maxAtk.atkValue >= maxDef.defValue)
	{
		flag = 1;
		it = chessChain.begin();
		while (it != chessChain.end())
		{
			if ((*it).atkValue == maxAtk.atkValue) secondWeight.push_back(*it);
			it++;
		}
	}
	else
	{
		flag = 2;
		it = chessChain.begin();
		while (it != chessChain.end())
		{
			if ((*it).defValue == maxDef.defValue) secondWeight.push_back(*it);
			it++;
		}
	}

	//在OJ中会显示超时
	it = secondWeight.begin();
	Chess temMax;
	if (flag == 1)//如果maxAtk大
	{
		temMax = *it;//找次位权的最大值
		while (it != secondWeight.end())
		{
			if ((*it).defValue >= temMax.defValue) temMax = *it;
			it++;
		}
	}
	else//如果maxDef大
	{
		temMax = *it;//找次位权的最大值
		while (it != secondWeight.end())
		{
			if ((*it).atkValue >= temMax.atkValue) temMax = *it;
			it++;
		}
	}


	int n = 0;//记录次位权值最大值个数
	vector<Chess> secondWeightBest;//存放第二位权的最大值链<---如果不止一个还要随机取一个
	it = secondWeight.begin();
	if (flag == 1)//如果maxValue大
	{
		while (it != secondWeight.end())
		{
			if ((*it).defValue == temMax.defValue)
			{
				secondWeightBest.push_back(*it);
				n++;
			}
			it++;
		}
	}
	else
	{
		while (it != secondWeight.end())
		{
			if ((*it).atkValue == temMax.atkValue)
			{
				secondWeightBest.push_back(*it);
				n++;
			}
			it++;
		}
	}
	if (n == 1) return secondWeightBest[0];
	int loc = Random_location(n);//生成0~n-1 的随机数，所谓所选择的棋子；
	return secondWeightBest[loc];
	/*if(maxAtk.atkValue>maxDef.defValue) return maxAtk;
	else return maxDef;*/
}

int Robot::AI(Map xm, int color,int order)
{	
	//AI落子，空位赋权值，权值最大者放棋盘
	//第一回合必下天元,最后返回order
	if (order == 1)
	{
		if (xm.getNum() == 0 && color == 0)
		{
			//当棋盘全空的时候且人机执黑，人机人在天元(8,8)下子
			putChess(xm, Chess((xm.getSize() + 1) / 2, (xm.getSize() + 1) / 2));

		}
		else //玩家执黑
		{
			//当棋盘全空的时候且人机执白，玩家在天元(8,8)下子
			putChessman(xm, Chess((xm.getSize() + 1) / 2, (xm.getSize() + 1) / 2));
			giveChess_value(xm);
			Chess xe = getBestChess(xm);
			putChess(xm, xe);
		}
		order++;
	}
	else//非第一回合
	{
		giveChess_value(xm);
		Chess xe = getBestChess(xm);
		putChess(xm, xe);
	}
	return order;//返回order
}

int Robot::Random_location(int n)
{
	srand((int)time(0));
	int x = rand() % n;
	return x;
}

int Robot::getInput()
{
	std::string x;
	std::cin >> x;
	if (x == "a" || x == "A") return 1;
	if (x == "b" || x == "B") return 2;
	if (x == "c" || x == "C") return 3;
	if (x == "d" || x == "D") return 4;
	if (x == "e" || x == "E") return 5;
	if (x == "f" || x == "F") return 6;
	if (x == "g" || x == "G") return 7;
	if (x == "h" || x == "H") return 8;
	if (x == "i" || x == "I") return 9;
	if (x == "j" || x == "J") return 10;
	if (x == "k" || x == "K") return 11;
	if (x == "l" || x == "L") return 12;
	if (x == "m" || x == "M") return 13;
	if (x == "n" || x == "N") return 14;
	if (x == "o" || x == "O") return 15;
	int a = atoi(x.c_str());
	return a;
}

int Robot::Input_x_OK(Map xm, Chess xe)
{
	//检查输入是否合法
	if (xe.col<1 || xe.col>xm.getSize() || xe.row<1 || xe.row>xm.getSize() ||
		xm.getChess(xe.row, xe.col).color != XNO) return 0;
	else return 1;
}

int Robot::getAtkValue(Map xm, Chess xe)
{
	int Chess_value[7] = { 0 };
	//七种棋型D个数存入数组
	Chess_value[0]=xm.count_L5(xe);
	Chess_value[1]=xm.count_A4(xe);
	Chess_value[2]=xm.count_R4(xe);
	Chess_value[3]=xm.count_A3(xe);
	Chess_value[4]=xm.count_S3(xe);
	Chess_value[5]=xm.count_A2(xe);
	Chess_value[6]=xm.count_S2(xe);
	int atkValue=0;
	atkValue+=Chess_value[0]*Va2;
	atkValue+=Chess_value[1]*Va5;
	atkValue+=Forbidden_move(Chess_value)*Va6;
	atkValue+=Chess_value[2]*Va8;
	atkValue+=Chess_value[3]*Va10;
	atkValue+=Chess_value[4]*Va12;
	atkValue+=Chess_value[5]*Va14;
	atkValue+=Chess_value[6]*Va15;
	return atkValue;
}

int Robot::getDefValue(Map xm, Chess xe)
{
	//friendColor与enemyColor互换
	xm.Friend_x_Enemy();

	int Chess_value[7] = {0};
	//七种棋型S个数存入数组
	Chess_value[0]=xm.count_L5(xe);
	Chess_value[1]=xm.count_A4(xe);
	Chess_value[2]=xm.count_R4(xe);
	Chess_value[3]=xm.count_A3(xe);
	Chess_value[4]=xm.count_S3(xe);
	Chess_value[5]=xm.count_A2(xe);
	Chess_value[6]=xm.count_S2(xe);
	int defValue=0;
	defValue+=Chess_value[0]*Va3;
	defValue+=Chess_value[1]*Va4;
	defValue+=Forbidden_move(Chess_value)*Va7;
	defValue+=Chess_value[2]*Va9;
	defValue+=Chess_value[3]*Va11;
	defValue+=Chess_value[4]*Va13;
	defValue+=Chess_value[5]*Va15/2;
	defValue+=Chess_value[6]*Va15/2/2;

	//用完换回
	xm.Friend_x_Enemy();
	return defValue;
}

int Robot::Forbidden_move(int Chess_value[])
{
	//检查是否禁手
	int count=0;
	if(Chess_value[3]>=2) count++;//三三禁手
	if(Chess_value[1]>=2 || Chess_value[2]>=2 || (Chess_value[1]&&Chess_value[2])) count++;//四四禁手
	if (Chess_value[0]>=1) count++; //长连禁手
	return count;
}

int Robot::WinnerCheck(Map xm)
{
	//检查胜者与同色连子
	for(int i=1;i<=xm.getSize();i++)
	{
		for(int j=1;j<=xm.getSize();j++)
		{
			if(xm.getChess(i,j).color==xm.Friend_Color() && xm.count_L5(Chess(i,j))>0) 
				return 1;//1是人机赢

			if(xm.getChess(i,j).color==xm.Friend_Color() && xm.count_L5(Chess(i,j))>0) 
			{
				xm.Friend_x_Enemy();
				return 2;//2是玩家赢
			}
			xm.Friend_x_Enemy();//原来的敌人又变回朋友
		}
	}
	return 0;
}

void Robot::giveChess_value(Map xm)
{
	for (int i = 1; i <= xm.getSize(); i++)
	{
		for (int j = 1; j <= xm.getSize(); j++)
		{
			Chess temXe = xm.getChess(i, j);
			if (temXe.color == XNO)
			{
				xm.setAtkValue(temXe, getAtkValue(xm, temXe));
				xm.setDefValue(temXe, getDefValue(xm, temXe));
			}
		}
	}
	return;
}

void Robot::Atk_x_Def(Map xm)
{
	//输出攻防得分
	Draw dw;
	for (int i = 1; i <= xm.getSize(); i++)
	{
		for (int j = 1; j <= xm.getSize(); j++)
		{
			std::cout << xm.getAtkValue(Chess(i, j)) << " ";
		}
		std::cout << std::endl;
	}
	dw.PrintEPTLines(3);
	for (int i = 1; i <= xm.getSize(); i++)
	{
		for (int j = 1; j <= xm.getSize(); j++)
		{
			std::cout << xm.getDefValue(Chess(i, j)) << " ";
		}
		std::cout << std::endl;
	}
	return;
}

void Robot::putChess(Map xm, Chess xe)
{
	xm.putAIChess(xm,xe);
	return;
}

void Robot::putChessman(Map xm, Chess xe)
{
	xm.putPlayChess(xe);
	return;
}

