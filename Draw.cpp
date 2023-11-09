#include "Draw.h"
#include "Map.h"
#include "Robot.h"
#include <iostream>
#include <string>
#include <Windows.h>

Draw::Draw(void)
{
}

Draw::~Draw(void)
{
}

void Draw::Draw_map(Map xm)
{
	/*
	打印棋子&棋盘
	┎┬┬┬┬┒
	┠┼○●┼┨
	┠┼┼●┼┨
	┠┼┼┼┼┨
	┖┷┷┷┷┚  
	*/
	char number[15] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O' };//字母A-O表示1-15。
	PrintEPTLines(2);
	PrintSpc(7);
	for (int i = 1; i <= xm.getSize(); i++)
	{
		std::cout << number[i - 1] << " ";
	}
	PrintEPTLines(1);
	PrintSpc(5);
	PrintString("┎");
	for (int i = 1; i <= xm.getSize(); i++) PrintString(" ┬");
	PrintString(" ┒");
	PrintEPTLines(1);
	for (int i = 1; i <= xm.getSize(); i++)
	{
		PrintSpc(4);
		std::cout << number[i - 1];
		PrintString("┠ ");
		for (int j = 1; j <= xm.getSize(); j++)
		{
			if (xm.getChess(i, j).color == XNO) PrintString("┼ ");
			else if (xm.getChess(i, j).color == XB1) PrintString("○ "); //○为黑棋，●为白棋
			else PrintString("● ");
		}
		PrintString("┨");
		PrintEPTLines(1);
	}
	PrintSpc(5);
	PrintString("┖ ");
	for (int i = 1; i <= xm.getSize(); i++) PrintString("┷ ");
	PrintString("┚");
	PrintEPTLines(3);
}

void Draw::Error_x_Report() 
{
	system("cls");
	PrintEPTLines(5);
	PrintSpc(5);
	PrintString("输入错误，请重新输入！");
	PrintEPTLines(2);
	system("pause");
}

void Draw::Player_win(Map& xm) 
{
	system("cls");
	PrintEPTLines(10);
	PrintSpc(10);
	std::cout << "你赢了！" << std::endl;
	Sleep(2500);
	system("cls");
	Draw_map(xm);
}

void Draw::Player_loss(Map& xm) 
{
	system("cls");
	PrintEPTLines(10);
	PrintSpc(10);
	std::cout << "你输了！" << std::endl;
	Sleep(2500);
	system("cls");
	Draw_map(xm);
}

void Draw::PrintEPTLines(int n) 
{
	for (int i = 0; i < n; i++) std::cout << std::endl;
}

void Draw::PrintSpc(int n) 
{
	for (int i = 0; i < n; i++) std::cout << " ";
}

void Draw::PrintString(const std::string& str) 
{
	std::cout << str;
}

void Draw::PrintMessage(int color) 
{
	PrintEPTLines(1);
	PrintString("A1 B2 C3 D4 E5 F6 G7 H8 I9 J10 K11 L12 M13 N14 O15 \n");
	PrintEPTLines(2);
	if (color == 1) {
		PrintString("请输入下一棋的坐标(黑棋) 例: A/1 回车/空格 B/2 :");
	}
	else {
		PrintString("请输入下一棋的坐标(白棋) 例: A/1 回车/空格 B/2 :");
	}
}