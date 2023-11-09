#include "Robot.h"
#include "Draw.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <random>
#include <windows.h>
#include <limits>

using namespace std;

void showchs(const string& player, int chs);
int getValidchs();
int decideOrder();
void playGame(Map& xm, Robot& cr, Draw& dr, int color);

const string Chc[] = { "石头", "布", "剪刀" };

int main() 
{
    Map xm;
    Robot cr;
    Draw dr;

    int color = decideOrder();
    if (color == 0)
    {
        xm.Color_x_Initialize(XB1);//人机先手执黑子，玩家执白子
    }
    else
    {
        xm.Color_x_Initialize(XW0);//人机后手执白子，玩家执黑子
    }

    xm.Map_x_Initialize(15);
    dr.Draw_map(xm);

    playGame(xm, cr, dr, color);
    return 0;
}

void showchs(const string& player, int chs) 
{
    cout << "\n " << player << "选择了 " << Chc[chs - 1] << "! \n";
}

int getValidchs() 
{
    int chs;
    while (true) {
        cout << " ";
        if (!(cin >> chs) || chs < 1 || chs > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n 无效输入，请重新输入: \n\n";
        }
        else {
            return chs;
        }
    }
}

int decideOrder() 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 3);

    cout << "\n 石头剪刀布决定先后: \n\n 石头 = 1  布 = 2  剪刀 = 3 \n\n";
    int player_p = getValidchs();
    int machine_p = distrib(gen);
    int tietime = 0;

    showchs("玩家", player_p);
    showchs("人机", machine_p);

    while (player_p == machine_p) 
    {
        tietime++;
        cout << "\n 平局 " << tietime <<"次 请重新输入: \n\n";
        player_p = getValidchs();
        machine_p = distrib(gen);
        showchs("玩家", player_p);
        showchs("人机", machine_p);
    }
    
    // 确定赢家和游戏顺序
    bool player_wins = (player_p == 1 && machine_p == 3) || (player_p == 2 && machine_p == 1) || (player_p == 3 && machine_p == 2);
    cout << (player_wins ? "\n 你获胜，玩家先手。\n" : "\n 人机获胜，人机先手。\n");

    // 清屏并继续游戏
    cout << "\n ";
    system("pause");
    system("cls");

    return player_wins;
}

void playGame(Map& xm, Robot& cr, Draw& dr, int color) 
{
    int order = 1;
    int result = 0;
    while (true) 
    {
        order = cr.AI(xm, color, order);//传参 color，order
        system("cls");
        dr.Draw_map(xm);
        result = cr.WinnerCheck(xm);
        if (result == 1) break;

        dr.PrintMessage(color);
        while (true) 
        {
            int x = cr.getInput();
            int y = cr.getInput();
            if (cr.Input_x_OK(xm, Chess(x, y))) {
                xm.putPlayChess(Chess(x, y));
                system("cls");
                dr.Draw_map(xm);
                break;
            }
            else {
                dr.Error_x_Report();
                system("cls");
                dr.Draw_map(xm);
                dr.PrintMessage(color);
                continue;
            }
        }

        result = cr.WinnerCheck(xm);
        if (result == 2)
        {
            Sleep(2000);
            break;
        }
    }

    result == 1 ? dr.Player_loss(xm) : dr.Player_win(xm);
    system("pause");
}