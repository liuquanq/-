#include "Map.h"
#include "Draw.h"
#include <iostream>
#include<vector>
#include <Windows.h>

Map::Map(void)
{
	num=0;
}

Map::~Map(void)
{
}

Chess Map::getNext(Chess xe, int dir)
{
	//若被查找棋子本身超出边界 则返回错误棋子
	if (xe.col < 0 || xe.isBoundry == true) return getErrorChess();
	Chess tem;
	switch (dir)
	{
	case XLAY:
		tem = right_Next(xe);
		break;
	case XSTD:
		tem = down_Next(xe);
		break;
	case XMAN:
		tem = right_down_Next(xe);
		break;
	case XICE:
		tem = right_up_Next(xe);
		break;
	default:
		break;
	}
	if (tem.col < 0 || tem.isBoundry == true) return Chess("XERRO");
	return tem;
}

Chess Map::getPrev(Chess xe, int dir)
{
	if (xe.col < 0 || xe.isBoundry == true) return getErrorChess();
	Chess tem;
	switch (dir)
	{
	case XLAY:
		tem = left_Next(xe);
		break;
	case XSTD:
		tem = up_Next(xe);
		break;
	case XMAN:
		tem = left_up_Next(xe);
		break;
	case XICE:
		tem = left_down_Next(xe);
		break;
	default:
		break;
	}
	if (tem.col < 0 || tem.isBoundry == true) return Chess("XERRO");
	return tem;
}

Chess Map::getChess(int x, int y)
{
	return map[x][y];
}

Chess Map::up_Next(Chess xe)
{
	if (xe.row <= 0) return getErrorChess();
	Chess tem = Chess(map[xe.row - 1][xe.col].color,
		map[xe.row - 1][xe.col].atkValue,
		map[xe.row - 1][xe.col].defValue,
		map[xe.row - 1][xe.col].row,
		map[xe.row - 1][xe.col].col,
		map[xe.row - 1][xe.col].isBoundry);
	return tem;
}

Chess Map::down_Next(Chess xe)
{
	if (xe.row >= size + 1) return getErrorChess();
	Chess tem = Chess(map[xe.row + 1][xe.col].color,
		map[xe.row + 1][xe.col].atkValue,
		map[xe.row + 1][xe.col].defValue,
		map[xe.row + 1][xe.col].row,
		map[xe.row + 1][xe.col].col,
		map[xe.row + 1][xe.col].isBoundry);
	return tem;
}

Chess Map::left_Next(Chess xe)
{
	if (xe.col <= 0) return getErrorChess();
	Chess tem = Chess(map[xe.row][xe.col - 1].color,
		map[xe.row][xe.col - 1].atkValue,
		map[xe.row][xe.col - 1].defValue,
		map[xe.row][xe.col - 1].row,
		map[xe.row][xe.col - 1].col,
		map[xe.row][xe.col - 1].isBoundry);
	return tem;
}

Chess Map::right_Next(Chess xe)
{
	if (xe.col >= size + 1) return getErrorChess();
	Chess tem = Chess(map[xe.row][xe.col + 1].color,
		map[xe.row][xe.col + 1].atkValue,
		map[xe.row][xe.col + 1].defValue,
		map[xe.row][xe.col + 1].row,
		map[xe.row][xe.col + 1].col,
		map[xe.row][xe.col + 1].isBoundry);
	return tem;
}

Chess Map::left_up_Next(Chess xe)
{
	if (xe.row <= 0 || xe.col <= 0) return getErrorChess();
	Chess tem = Chess(map[xe.row - 1][xe.col - 1].color,
		map[xe.row - 1][xe.col - 1].atkValue,
		map[xe.row - 1][xe.col - 1].defValue,
		map[xe.row - 1][xe.col - 1].row,
		map[xe.row - 1][xe.col - 1].col,
		map[xe.row - 1][xe.col - 1].isBoundry);
	return tem;
}

Chess Map::right_up_Next(Chess xe)
{
	if (xe.row <= 0 || xe.col >= size + 1) return getErrorChess();
	Chess tem = Chess(map[xe.row - 1][xe.col + 1].color,
		map[xe.row - 1][xe.col + 1].atkValue,
		map[xe.row - 1][xe.col + 1].defValue,
		map[xe.row - 1][xe.col + 1].row,
		map[xe.row - 1][xe.col + 1].col,
		map[xe.row - 1][xe.col + 1].isBoundry);
	return tem;
}

Chess Map::left_down_Next(Chess xe)
{
	if (xe.row >= size + 1 || xe.col <= 0) return getErrorChess();
	Chess tem = Chess(map[xe.row + 1][xe.col - 1].color,
		map[xe.row + 1][xe.col - 1].atkValue,
		map[xe.row + 1][xe.col - 1].defValue,
		map[xe.row + 1][xe.col - 1].row,
		map[xe.row + 1][xe.col - 1].col,
		map[xe.row + 1][xe.col - 1].isBoundry);
	return tem;
}

Chess Map::right_down_Next(Chess xe)
{
	if (xe.row >= size + 1 || xe.col >= size + 1) return getErrorChess();
	Chess tem = Chess(map[xe.row + 1][xe.col + 1].color,
		map[xe.row + 1][xe.col + 1].atkValue,
		map[xe.row + 1][xe.col + 1].defValue,
		map[xe.row + 1][xe.col + 1].row,
		map[xe.row + 1][xe.col + 1].col,
		map[xe.row + 1][xe.col + 1].isBoundry);
	return tem;
}

Chess Map::getErrorChess()
{
	Chess xe = Chess(XERRO, XERRO, XERRO, XERRO, XERRO, true);
	return xe;
}

int Map::up(Chess xe)
{
	int count = 0;
	xe.row--;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.row--;
	}
	return count;
}

int Map::down(Chess xe)
{
	int count = 0;
	xe.row++;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.row++;
	}
	return count;
}

int Map::left(Chess xe)
{
	int count = 0;
	xe.col--;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.col--;
	}
	return count;
}

int Map::right(Chess xe)
{
	int count = 0;
	xe.col++;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.col++;
	}
	return count;
}

int Map::left_up(Chess xe)
{
	int count = 0;
	xe.row--;
	xe.col--;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.row--;
		xe.col--;
	}
	return count;
}

int Map::right_up(Chess xe)
{
	int count = 0;
	xe.row--;
	xe.col++;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.row--;
		xe.col++;
	}
	return count;
}

int Map::left_down(Chess xe)
{
	int count = 0;
	xe.row++; xe.col--;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.row++;
		xe.col--;
	}
	return count;
}

int Map::right_down(Chess xe)
{
	int count = 0;
	xe.row++; xe.col++;
	while (map[xe.row][xe.col].color == friendColor)
	{
		count++;
		xe.row++;
		xe.col++;
	}
	return count;
}

int Map::getSize()
{
	return size;
}

int Map::getAtkValue(Chess xe)
{
	return map[xe.row][xe.col].atkValue;
}

int Map::getDefValue(Chess xe)
{
	return map[xe.row][xe.col].defValue;
}

int Map::getNum(Chess xe, int dir)
{
	switch (dir)
	{
	case XLAY:
		return getLayNum(xe);
	case XSTD:
		return getStandNum(xe);
	case XMAN:
		return getMainNum(xe);
	case XICE:
		return getVixeNum(xe);
	default:
		return 0;
	}
}

int Map::getNum()
{
	return this->num;
}

int Map::getLayNum(Chess xe)
{
	int count = 0;
	count += left(xe);
	count += right(xe);
	return count + 1;
}

int Map::getStandNum(Chess xe)
{
	int count = 0;
	count += up(xe);
	count += down(xe);
	return count + 1;
}

int Map::getMainNum(Chess xe)
{
	int count = 0;
	count += left_up(xe);
	count += right_down(xe);
	return count + 1;
}

int Map::getVixeNum(Chess xe)
{
	int count = 0;
	count += right_up(xe);
	count += left_down(xe);
	return count + 1;
}

int Map::Friend_Color()
{
	return this->friendColor;
}

int Map::L5(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5)
{
	if (xe1.color == xe2.color &&
		xe2.color == xe3.color &&
		xe3.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor) return 1;
	return 0;
}

int Map::A4(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6)
{
	if (xe1.color == xe6.color &&
		xe6.color == XNO &&
		xe2.color == xe3.color &&
		xe3.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor) return 1;
	return 0;
}

int Map::R4(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6)
{
	if ((xe2.color == xe3.color &&
		xe3.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor &&
		xe1.color == XNO &&
		xe6.color == enemyColor) ||
		(xe2.color == xe3.color &&
			xe3.color == xe4.color &&
			xe4.color == xe5.color &&
			xe5.color == friendColor &&
			xe6.color == XNO &&
			xe1.color == enemyColor)) return 1;
	return 0;
}

int Map::R4(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5)
{
	if ((xe1.color == xe2.color &&
		xe2.color == xe3.color &&
		xe3.color == xe5.color &&
		xe5.color == friendColor &&
		xe4.color == XNO) ||
		(xe1.color == xe4.color &&
			xe4.color == xe3.color &&
			xe3.color == xe5.color &&
			xe5.color == friendColor &&
			xe2.color == XNO)) return 1;
	if (xe1.color == xe2.color &&
		xe2.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor &&
		xe3.color == XNO) return 1;
	return 0;
}

int Map::A3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5)
{
	if (xe1.color == xe5.color &&
		xe5.color == XNO &&
		xe2.color == xe3.color &&
		xe3.color == xe4.color &&
		xe4.color == friendColor) return 1;
	return 0;
}

int Map::A3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6)
{
	if ((xe1.color == xe4.color &&
		xe4.color == xe6.color &&
		xe6.color == XNO &&
		xe2.color == xe3.color &&
		xe3.color == xe5.color &&
		xe5.color == friendColor) ||
		(xe1.color == xe3.color &&
			xe3.color == xe6.color &&
			xe6.color == XNO &&
			xe2.color == xe4.color &&
			xe4.color == xe5.color &&
			xe5.color == friendColor)) return 1;
	return 0;
}

int Map::S3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5)
{
	if (xe1.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor &&
		xe2.color == xe3.color &&
		xe3.color == XNO) return 1;
	if (xe1.color == xe2.color &&
		xe2.color == xe5.color &&
		xe5.color == friendColor &&
		xe4.color == xe3.color &&
		xe3.color == XNO) return 1;
	if (xe1.color == xe3.color &&
		xe3.color == xe5.color &&
		xe5.color == friendColor &&
		xe2.color == xe4.color &&
		xe4.color == XNO) return 1;
	return 0;
}

int Map::S3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6)
{
	if (xe1.color == xe2.color &&
		xe2.color == XNO &&
		xe3.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor &&
		xe6.color == enemyColor) return 1;
	if (xe5.color == xe6.color &&
		xe6.color == XNO &&
		xe3.color == xe4.color &&
		xe4.color == xe2.color &&
		xe2.color == friendColor &&
		xe1.color == enemyColor) return 1;
	if (xe1.color == xe3.color &&
		xe3.color == XNO &&
		xe2.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor &&
		xe6.color == enemyColor) return 1;
	if (xe4.color == xe6.color &&
		xe6.color == XNO &&
		xe2.color == xe3.color &&
		xe3.color == xe5.color &&
		xe5.color == friendColor &&
		xe1.color == enemyColor) return 1;
	if (xe1.color == xe4.color &&
		xe4.color == XNO &&
		xe2.color == xe3.color &&
		xe3.color == xe5.color &&
		xe5.color == friendColor &&
		xe6.color == enemyColor) return 1;
	if (xe3.color == xe6.color &&
		xe6.color == XNO &&
		xe2.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor &&
		xe1.color == enemyColor) return 1;
	return 0;
}

int Map::S3(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6, Chess xe7)
{
	if (xe1.color == xe7.color &&
		xe7.color == enemyColor &&
		xe2.color == xe6.color &&
		xe6.color == XNO &&
		xe3.color == xe4.color &&
		xe4.color == xe5.color &&
		xe5.color == friendColor) return 1;
	return 0;
}

int Map::A2(Chess xe1, Chess xe2, Chess xe3, Chess xe4)
{
	if (xe1.color == xe4.color &&
		xe4.color == friendColor &&
		xe2.color == xe3.color &&
		xe3.color == XNO) return 1;
	return 0;
}

int Map::A2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5)
{
	if (xe1.color == xe3.color &&
		xe3.color == xe5.color &&
		xe5.color == XNO &&
		xe2.color == xe4.color &&
		xe4.color == friendColor) return 1;
	return 0;
}

int Map::A2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6)
{
	if (xe1.color == xe2.color &&
		xe2.color == xe5.color &&
		xe5.color == xe6.color &&
		xe6.color == XNO &&
		xe3.color == xe4.color &&
		xe4.color == friendColor) return 1;
	return 0;
}

int Map::S2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5)
{
	if (xe1.color == xe5.color &&
		xe5.color == friendColor &&
		xe2.color == xe3.color &&
		xe3.color == xe4.color &&
		xe4.color == XNO) return 1;
	return 0;
}

int Map::S2(Chess xe1, Chess xe2, Chess xe3, Chess xe4, Chess xe5, Chess xe6)
{
	if (xe1.color == xe2.color &&
		xe2.color == xe3.color &&
		xe3.color == XNO &&
		xe5.color == xe4.color &&
		xe4.color == friendColor &&
		xe6.color == enemyColor) return 1;
	if (xe4.color == xe5.color &&
		xe5.color == xe6.color &&
		xe6.color == XNO &&
		xe2.color == xe3.color &&
		xe3.color == friendColor &&
		xe1.color == enemyColor) return 1;
	if (xe1.color == xe2.color &&
		xe2.color == xe4.color &&
		xe4.color == XNO &&
		xe5.color == xe3.color &&
		xe3.color == friendColor &&
		xe6.color == enemyColor) return 1;
	if (xe5.color == xe6.color &&
		xe6.color == xe3.color &&
		xe3.color == XNO &&
		xe2.color == xe4.color &&
		xe4.color == friendColor &&
		xe1.color == enemyColor) return 1;
	if (xe1.color == xe3.color &&
		xe3.color == xe4.color &&
		xe4.color == XNO &&
		xe2.color == xe5.color &&
		xe5.color == friendColor &&
		xe6.color == enemyColor) return 1;
	if (xe3.color == xe4.color &&
		xe4.color == xe6.color &&
		xe6.color == XNO &&
		xe2.color == xe5.color &&
		xe5.color == friendColor &&
		xe1.color == enemyColor) return 1;
	return 0;
}

int Map::L5(std::vector<Chess> xe, int n)
{
	if (n == 5) return L5(xe[0], xe[1], xe[2], xe[3], xe[4]);
	return 0;
}

int Map::A4(std::vector<Chess> xe, int n)
{
	if (n == 6) return A4(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5]);
	return 0;
}

int Map::R4(std::vector<Chess> xe, int n)
{
	int count = 0;
	if (n == 5) count += R4(xe[0], xe[1], xe[2], xe[3], xe[4]);
	if (n == 6) count += R4(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5]);
	return count;
}

int Map::A3(std::vector<Chess> xe, int n)
{
	int count = 0;
	if (n == 5) count += A3(xe[0], xe[1], xe[2], xe[3], xe[4]);
	if (n == 6) count += A3(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5]);
	return count;
}

int Map::S3(std::vector<Chess> xe, int n)
{
	int count = 0;
	if (n == 5) count += S3(xe[0], xe[1], xe[2], xe[3], xe[4]);
	if (n == 6) count += S3(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5]);
	if (n == 7) count += S3(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5], xe[6]);
	return count;
}

int Map::A2(std::vector<Chess> xe, int n)
{
	int count = 0;
	if (n == 4) count += A2(xe[0], xe[1], xe[2], xe[3]);
	if (n == 5) count += A2(xe[0], xe[1], xe[2], xe[3], xe[4]);
	if (n == 6) count += A2(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5]);
	return count;
}

int Map::S2(std::vector<Chess> xe, int n)
{
	int count = 0;
	if (n == 5) count += S2(xe[0], xe[1], xe[2], xe[3], xe[4]);
	if (n == 6) count += S2(xe[0], xe[1], xe[2], xe[3], xe[4], xe[5]);
	return count;
}

int Map::L5(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += L5(*it, n);
		it++;
	}
	return count;
}

int Map::A4(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += A4(*it, n);
		it++;
	}
	return count;
}

int Map::R4(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += R4(*it, n);
		it++;
	}
	return count;
}

int Map::A3(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += A3(*it, n);//<=====
		it++;
	}
	return count;
}

int Map::S3(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += S3(*it, n);
		it++;
	}
	return count;
}

int Map::A2(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += A2(*it, n);
		it++;
	}
	return count;
}

int Map::S2(std::vector<std::vector<Chess>> xe, int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count = 0;
	it = xe.begin();
	while (it != xe.end())
	{
		if (!XB1_x_OK((*it)))
		{
			it++;
			continue;
		}
		count += S2(*it, n);
		it++;
	}
	return count;
}

int Map::count_L5(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 1; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 5, i);
		if (!Chain_x_OK(vxe)) continue;
		count += L5(vxe, 5);
	}
	return count;
}

int Map::count_A4(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 2; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 6, i);
		if (!Chain_x_OK(vxe)) continue;
		count += A4(vxe, 6);
	}
	return count;
}

int Map::count_R4(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 2; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 6, i);
		if (!Chain_x_OK(vxe)) continue;
		count += R4(vxe, 6);
	}
	for (int i = 1; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 5, i);
		if (!Chain_x_OK(vxe)) continue;
		count += R4(vxe, 5);
	}
	return count;
}

int Map::count_A3(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 2; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 6, i);
		if (!Chain_x_OK(vxe)) continue;
		count += A3(vxe, 6);//<====
	}
	for (int i = 2; i <= 4; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 5, i);
		if (!Chain_x_OK(vxe)) continue;
		count += A3(vxe, 5);
	}
	return count;
}

int Map::count_S3(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 3; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 7, i);
		if (!Chain_x_OK(vxe)) continue;
		count += S3(vxe, 7);
	}
	for (int i = 2; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 6, i);
		if (!Chain_x_OK(vxe)) continue;
		count += S3(vxe, 6);
	}
	for (int i = 1; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 5, i);
		if (!Chain_x_OK(vxe)) continue;
		count += S3(vxe, 5);
	}
	return count;
}

int Map::count_A2(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 3; i <= 4; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 6, i);
		if (!Chain_x_OK(vxe)) continue;
		count += A2(vxe, 6);
	}
	for (int i = 2; i <= 4; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 5, i);
		if (!Chain_x_OK(vxe)) continue;
		count += A2(vxe, 5);
	}
	for (int i = 1; i <= 4; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 4, i);
		if (!Chain_x_OK(vxe)) continue;
		count += A2(vxe, 4);
	}
	return count;
}

int Map::count_S2(Chess xe)
{
	using std::vector;
	int count = 0;
	for (int i = 2; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 6, i);
		if (!Chain_x_OK(vxe)) continue;
		count += S2(vxe, 6);
	}
	for (int i = 1; i <= 5; i++)
	{
		vector<vector<Chess>> vxe = getChessChain(xe, 5, i);
		if (!Chain_x_OK(vxe)) continue;
		count += S2(vxe, 5);
	}
	return count;
}

void Map::Map_x_Initialize(int size)
{
	this->size=size;
	this->map=new Chess *[size+2];//申请的空间比棋盘大一，使棋盘从1开始
	for(int i=0;i<size+2;i++) map[i]=new Chess[size+2];
	for(int j=0;j<size+1;j++) map[0][j]=Chess(XNO,-1,-1,0,j,true); 
	for(int i=0;i<size+1;i++) map[i][0]=Chess(XNO,-1,-1,i,0,true);
	for(int i=0;i<size+2;i++) map[i][size+1]=Chess(XNO,-1,-1,i,size+1,true);
	for(int j=0;j<size+2;j++) map[size+1][j]=Chess(XNO,-1,-1,size+1,j,true);
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			map[i][j]=Chess(XNO,0,0,i,j,false);
		}
	}
}

void Map::setAtkValue(Chess xe,int atkValue)
{
	map[xe.row][xe.col].atkValue=atkValue;
	return;
}

void Map::setDefValue(Chess xe,int defValue)
{
	map[xe.row][xe.col].defValue=defValue;
	return;
}

void Map::Friend_Num()
{
	std::cout<< "请输入友方棋子个数" <<std::endl;
	int n;
	std::cin>>n;
	std::cout << "请输入" << n << "个棋子的位置" << std::endl;
	int x,y;
	for(int i=0;i<n;i++)
	{
		std::cin>>x>>y;
		map[x][y].color=friendColor;
	}
	//system("cls");
}

void Map::Enemy_Num()
{
	std::cout << "请输入敌方棋子个数" << std::endl;
	int n;
	std::cin>>n;
	std::cout << "请输入" << n << "个棋子的位置" << std::endl;
	int x,y;
	for(int i=0;i<n;i++)
	{
		std::cin>>x>>y;
		map[x][y].color=enemyColor;
	}
}

void Map::putAIChess(Map xm,Chess xe)
{	
	Draw dr;
	numPlus();
	system("cls");
	//dr.PrintEPTLines(5);
	map[xe.row][xe.col].color = friendColor;
	dr.Draw_map(xm);
	std::cout<<"人机子颜色: "<<define_string(map[xe.row][xe.col].color)<<std::endl;
	std::cout<<"人机落子位置: ("<<xe.row<<","<<xe.col<<")"<<std::endl;
	//system("pause");
	Sleep(2000);
	return;
}

void Map::putPlayChess(Chess xe)
{
	//玩家落子
	Draw dr;
	numPlus();
	map[xe.row][xe.col].color=enemyColor;
	return;
}

void Map::outputMap()
{
	for(int i=1;i<=size;i++)
	{
		for (int j=1;j<=size;j++)
		{;
			std::cout<<map[i][j].atkValue<<" ";
		}
		std::cout<<std::endl;
	}
}

void Map::Color_x_Initialize(int color)
{
	this->friendColor=color;
	if(friendColor==XB1) enemyColor=XW0;
	else enemyColor=XB1;
}

void Map::Friend_x_Enemy()
{
	if(this->friendColor==XB1)
	{
		this->friendColor=XW0;
		this->enemyColor=XB1;
	}
	else
	{
		this->friendColor=XB1;
		this->enemyColor=XW0;
	}
	return;
}

void Map::numPlus()
{
	this->num++;
}

void Map::outputChess(Chess xe)
{	
	std::cout<<"color:"<<define_string(xe.color)<<std::endl;
	std::cout<<"atkValue:"<<xe.atkValue<<std::endl;
	std::cout<<"defValue:"<<xe.defValue<<std::endl;
	std::cout<<"row & col: ("<<xe.row<<","<<xe.col<<")"<<std::endl;
	std::cout<<"isBoundry:"<<bool_string(xe.isBoundry)<<std::endl;
	Draw dw;
	dw.PrintEPTLines(2);
}

void Map::outputOneDVector(std::vector<Chess> xe)
{
	using std::vector;
	vector<Chess>::iterator it;
	it=xe.begin();
	while(it!=xe.end())
	{
		outputChess(*it);
		it++;
	}
	return;
}

void Map::outputTwoDVector(std::vector<std::vector<Chess>> xe)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	it=xe.begin();
	while(it!=xe.end())
	{
		outputOneDVector(*it);
		it++;
	}
}

std::vector<std::vector<Chess>> Map::getChessChain(Chess xe,int n,int loc)
{
	using std::vector;
	vector<Chess> vErrorXeTxm;
	vErrorXeTxm.push_back(getErrorChess());
	vector<vector<Chess>> vErrorXe;
	vErrorXe.push_back(vErrorXeTxm);
	vector<vector<Chess>> vxe;
	vector<Chess> vxeLay,vxeStand,vxeMain,vxeVixe;
	switch(n)
	{
	case 4:
		vxeLay=C4(xe,XLAY,loc);
		vxeStand=C4(xe,XSTD,loc);
		vxeMain=C4(xe,XMAN,loc);
		vxeVixe=C4(xe,XICE,loc);
		break;
	case 5:
		vxeLay=C5(xe,XLAY,loc);
		vxeStand=C5(xe,XSTD,loc);
		vxeMain=C5(xe,XMAN,loc);
		vxeVixe=C5(xe,XICE,loc);
		break;
	case 6:
		vxeLay=C6(xe,XLAY,loc);
		vxeStand=C6(xe,XSTD,loc);
		vxeMain=C6(xe,XMAN,loc);
		vxeVixe=C6(xe,XICE,loc);
		break;
	case 7:
		vxeLay=C7(xe,XLAY,loc);
		vxeStand=C7(xe,XSTD,loc);
		vxeMain=C7(xe,XMAN,loc);
		vxeVixe=C7(xe,XICE,loc);
		break;
	default:
		return vErrorXe;
	}
	vxe.push_back(vxeLay);
	vxe.push_back(vxeStand);
	vxe.push_back(vxeMain);
	vxe.push_back(vxeVixe);
	return vxe;
}

std::vector<Chess> Map::C4(Chess xe, int dir, int loc)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return D1(xe,4,dir);
	case 2:
		return D2(xe,4,dir);
	case 3:
		return D3(xe,4,dir);
	case 4:
		return D4(xe,4,dir);
	default:
		return vErrorXe;
	}
	return vErrorXe;
}

std::vector<Chess> Map::C5(Chess xe, int dir, int loc)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return D1(xe,5,dir);
	case 2:
		return D2(xe,5,dir);
	case 3:
		return D3(xe,5,dir);
	case 4:
		return D4(xe,5,dir);
	case 5:
		return D5(xe,5,dir);
	default:
		return vErrorXe;
	}
	return vErrorXe;
}

std::vector<Chess> Map::C6(Chess xe, int dir, int loc)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return D1(xe,6,dir);
	case 2:
		return D2(xe,6,dir);
	case 3:
		return D3(xe,6,dir);
	case 4:
		return D4(xe,6,dir);
	case 5:
		return D5(xe,6,dir);
	case 6:
		return D6(xe,6,dir);
	default:
		return vErrorXe;
	}
	return vErrorXe;
}

std::vector<Chess> Map::C7(Chess xe, int dir, int loc)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return D1(xe,7,dir);
	case 2:
		return D2(xe,7,dir);
	case 3:
		return D3(xe,7,dir);
	case 4:
		return D4(xe,7,dir);
	case 5:
		return D5(xe,7,dir);
	case 6:
		return D6(xe,7,dir);
	case 7:
		return D7(xe,7,dir);
	default:
		return vErrorXe;
	}
	return vErrorXe;
}

std::vector<Chess> Map::D1(Chess xe, int n, int dir)
{
	//错误数组，如果结果不合理，返回错误数组
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	//棋子位于棋链的位置1处，棋链长n,方向为dir
	std::vector<Chess> vxe;//用来存储该棋链
	if (n < 1) return vxe;//如果棋子的位置比棋链长还大，则不合常理
	Chess oxe = map[xe.row][xe.col];
	oxe.color = friendColor;//必须要将空白位改为friendColor，否则会影响判断！
	vxe.push_back(oxe);
	if(n==1) return vxe;
	for(int i=2;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}

	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::vector<Chess> Map::D2(Chess xe, int n, int dir)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	std::vector<Chess> vxe;
	if (n < 2) return vxe;
	Chess xe1 = getPrev(xe, dir);
	vxe.push_back(xe1);
	Chess oxe = map[xe.row][xe.col];
	oxe.color = friendColor;
	vxe.push_back(oxe);
	if(n==2) return vxe;
	for (int i=3;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}
	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::vector<Chess> Map::D3(Chess xe,int n,int dir)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	std::vector<Chess> vxe;
	if (n < 3) return vxe;
	Chess xe2 = getPrev(xe, dir);
	Chess xe1 = getPrev(xe2, dir);
	vxe.push_back(xe1);
	vxe.push_back(xe2);
	Chess oxe = map[xe.row][xe.col];
	oxe.color = friendColor;
	vxe.push_back(oxe);
	if(n==3) return vxe;
	for (int i=4;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}
	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::vector<Chess> Map::D4(Chess xe,int n,int dir)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	std::vector<Chess> vxe;
	if (n < 4) return vxe;
	Chess xe1;
	Chess xe2;
	Chess xe3;
	xe3=getPrev(xe,dir);
	xe2=getPrev(xe3,dir);
	xe1=getPrev(xe2,dir);
	vxe.push_back(xe1);
	vxe.push_back(xe2);
	vxe.push_back(xe3);
	Chess oxe=map[xe.row][xe.col];
	oxe.color = friendColor;
	vxe.push_back(oxe);
	if(n==4) return vxe;
	for (int i=5;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}
	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::vector<Chess> Map::D5(Chess xe,int n,int dir)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	std::vector<Chess> vxe;
	if (n < 5) return vxe;
	Chess xe1;
	Chess xe2;
	Chess xe3;
	Chess xe4;
	xe4=getPrev(xe,dir);
	xe3=getPrev(xe4,dir);
	xe2=getPrev(xe3,dir);
	xe1=getPrev(xe2,dir);
	vxe.push_back(xe1);
	vxe.push_back(xe2);
	vxe.push_back(xe3);
	vxe.push_back(xe4);
	Chess oxe=map[xe.row][xe.col];
	oxe.color = friendColor;
	vxe.push_back(oxe);
	if(n==5) return vxe;
	for (int i=6;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}
	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::vector<Chess> Map::D6(Chess xe,int n,int dir)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	std::vector<Chess> vxe;
	if (n < 6) return vxe;
	Chess xe1;
	Chess xe2;
	Chess xe3;
	Chess xe4;
	Chess xe5;
	xe5=getPrev(xe,dir);
	xe4=getPrev(xe5,dir);
	xe3=getPrev(xe4,dir);
	xe2=getPrev(xe3,dir);
	xe1=getPrev(xe2,dir);
	vxe.push_back(xe1);
	vxe.push_back(xe2);
	vxe.push_back(xe3);
	vxe.push_back(xe4);
	vxe.push_back(xe5);
	Chess oxe=map[xe.row][xe.col];
	oxe.color = friendColor;
	vxe.push_back(oxe);
	if(n==6) return vxe;
	for (int i=7;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}
	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::vector<Chess> Map::D7(Chess xe,int n,int dir)
{
	std::vector<Chess> vErrorXe;
	vErrorXe.push_back(getErrorChess());
	std::vector<Chess> vxe;
	if (n < 7) return vxe;
	Chess xe1;
	Chess xe2;
	Chess xe3;
	Chess xe4;
	Chess xe5;
	Chess xe6;
	xe6=getPrev(xe,dir);
	xe5=getPrev(xe6,dir);
	xe4=getPrev(xe5,dir);
	xe3=getPrev(xe4,dir);
	xe2=getPrev(xe3,dir);
	xe1=getPrev(xe2,dir);
	vxe.push_back(xe1);
	vxe.push_back(xe2);
	vxe.push_back(xe3);
	vxe.push_back(xe4);
	vxe.push_back(xe5);
	vxe.push_back(xe6);
	Chess oxe=map[xe.row][xe.col];
	oxe.color = friendColor;//必须要将空白位改为friendColor，否则会影响判断！
	vxe.push_back(oxe);
	if(n==7) return vxe;
	for (int i=8;i<=n;i++)
	{
		Chess temXe;
		temXe=getNext(vxe[i-2],dir);
		vxe.push_back(temXe);
	}
	for (int i=0;i<n;i++)
	{
		if(vxe[i].isBoundry) return vErrorXe;
	}
	return vxe;
}

std::string Map::define_string(int code)
{
	switch(code)
	{
	case XB1:
		return "XB1";
	case XW0:
		return "XW0";
	case XNO:
		return "XNO";
	case XLAY:
		return "XLAY";
	case XSTD:
		return "XSTD";
	case XMAN:
		return "XMAN";
	case XICE:
		return "XICE";
	default:
		return "XERRO";
	}
	return "XERRO";
}

std::string Map::bool_string(bool flag)
{
	switch(flag)
	{
	case true:
		return "true";
	case false:
		return "false";
	}
	return "false";
}

bool Map::XB1_x_OK(std::vector<Chess> xe)
{
	using std::vector;
	vector<Chess>::iterator it;
	it=xe.begin();
	while(it!=xe.end())
	{
		if((*it).isBoundry) return false;//如果是边界或者错误棋子，那么就不ok
		it++;
	}
	return true;
}

bool Map::Chain_x_OK(std::vector<std::vector<Chess>> vxe)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	it=vxe.begin();
	while(it!=vxe.end())
	{
		vector<Chess>::iterator it2;
		it2=(*it).begin();
		while(it2!=(*it).end())
		{
			if(!(*it2).isBoundry) return true;
			it2++;
		}
		it++;
	}
	return false;
}


