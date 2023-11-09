#pragma once

#include "Map.h"
#include <string>

class Draw
{
 public:

	Draw(void);
	~Draw(void);

	void Draw_map(Map xm);
	void Error_x_Report();
	void Player_win(Map& xm);
	void Player_loss(Map& xm);
	void PrintEPTLines(int n);
	void PrintSpc(int n);
	void PrintString(const std::string& str);
	void PrintMessage(int color);

};

