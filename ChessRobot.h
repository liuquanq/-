#pragma once
#include "Map.h"

#define ONE_VAL 67108864
#define TWO_VAL 67000000
#define THREE_VAL 8388608
#define FOUR_VAL 4194304
#define FIVE_VAL 2097152
#define SIX_VAL 1048576
#define SEVEN_VAL 524288
#define EIGHT_VAL 262144
#define NINE_VAL 131072
#define TEN_VAL 65536
#define ELEVEN_VAL 32768
#define TWELVE_VAL 16384
#define THIRTEEN_VAL 8192
#define FOURTEEN_VAL 4096
#define FIFTEEN_VAL 2048

class ChessRobot
{
public:
	ChessRobot(void);
	~ChessRobot(void);
	void AI(Map mp);
	void outputAtkDefValue(Map mp);
	int inputIsOk(Map mp,Chess ce);

	//************************************
	// Method:    someWin
	// FullName:  ChessRobot::someWin
	// Access:    private 
	// Returns:   int
	// Qualifier: �ж���û����Ӯ��0��û��Ӯ��1�ǻ�����Ӯ��2�����Ӯ
	// Parameter: Map mp
	//************************************
	int someWin(Map mp);
private:
	//************************************
	// Method:    giveAllValue
	// FullName:  ChessRobot::giveAllValue
	// Access:    public 
	// Returns:   void
	// Qualifier: ������ÿ����λ��ֵ
	//�������ʱ��̫����....
	// Parameter: Map mp
	//************************************
	void giveAllValue(Map mp);
	//************************************
	// Method:    getBestChess
	// FullName:  ChessRobot::getBestChess
	// Access:    public 
	// Returns:   Chess
	// Qualifier: ����������λ��
	//************************************
	Chess getBestChess(Map mp);
	void putChess(Map mp, Chess ce);


	//************************************
	// Method:    getAtkValue
	// FullName:  ChessRobot::getAtkValue
	// Access:    public 
	// Returns:   int
	// Qualifier: ����ÿ�����ӵĹ�������
	// Parameter: Map mp
	// Parameter: Chess ce
	//************************************
	int getAtkValue(Map mp, Chess ce);

	//************************************
	// Method:    getDefValue
	// FullName:  ChessRobot::getDefValue
	// Access:    public 
	// Returns:   int
	// Qualifier: ����ÿ�����ӵķ��ط���
	// Parameter: Map mp
	// Parameter: Chess ce
	//************************************
	int getDefValue(Map mp, Chess ce);
	int getFibHand(int allValue[]);
	int getRandomLocation(int n);
};

