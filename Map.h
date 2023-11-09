#pragma once
#include <string>
#include<vector>

#define LAY 801
#define STAND 802
#define MAIN 803
#define VICE 804

#define BLACK 811
#define WHITE 812
#define NONE 813

#define ERROR -123

struct Chess 
{
	int color;
	int atkValue;
	int defValue;
	int row;
	int col;
	bool isBoundry;
	Chess(){this->isBoundry=false;};//һ������¶����Ǳ߽磬ֻ���ڳ�ʼ��ֵ��������б߽�

	//************************************
	// Method:    Chess
	// FullName:  Chess::Chess
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: int color ��ǰ��λ����ɫ
	// Parameter: int atkValue ��Ϊ��������Ȩֵ
	// Parameter: int defValue ��Ϊ���ط���Ȩֵ
	// Parameter: int x ������
	// Parameter: int y ������
	// Parameter: bool isBoundry �ж��ǲ��Ǳ߽�
	//************************************
	Chess(int color,int atkValue,int defValue,int x,int y,bool isBoundry)
	{
		this->color=color;
		this->atkValue=atkValue;
		this->defValue=defValue;
		this->row=x;
		this->col=y;
		this->isBoundry=isBoundry;
	}
	Chess(int color,int atkValue,int defValue)
	{
		this->color=color;
		this->atkValue=atkValue;
		this->defValue=defValue;
		this->isBoundry=false;
	}
	Chess(int color)
	{
		this->color=color;
		this->isBoundry=false;
	}
	Chess(int x,int y)
	{
		this->row=x;
		this->col=y;
		this->isBoundry=false;
	}
	Chess(std::string error)
	{
		this->color=ERROR;
		this->atkValue=ERROR;
		this->defValue=ERROR;
		this->row=ERROR;
		this->col=ERROR;
		this->isBoundry=true;
	}
};

class Map
{
private:
	int size;
	Chess **map;
	int friendColor;
	int enemyColor;
	int num;//��¼ȫ��������
public:
	Map(void);
	~Map(void);
	void iniMap(int size);
	int getSize();
	int getFriendColor();
	int getNum();
	void numPlus();
	void setAtkValue(Chess ce,int atkValue);
	void setDefValue(Chess ce,int defValue);
	int getAtkValue(Chess ce);
	int getDefValue(Chess ce);
	//************************************
	// Method:    giveMapValue
	// FullName:  Map::giveMapValue
	// Access:    public 
	// Returns:   void
	// Qualifier: ����ʹ�ã����������ѷ���������
	//************************************
	void giveMapFriend();
	void giveMapEnemy();

	void putAIChess(Chess ce);
	void putPlayChess(Chess ce);
	
	//************************************
	// Method:    outputMap
	// FullName:  Map::outputMap
	// Access:    public 
	// Returns:   void
	// Qualifier: ����������̵���ֵ��������
	//************************************
	void outputMap();

	//************************************
	// Method:    iniColor
	// FullName:  Map::iniColor
	// Access:    public 
	// Returns:   void
	// Qualifier: ��ʼ�������˵�������ɫ����Ϊ����ĵ�һ�˳��ǻ�����
	//ֻ��������ֵ���з����Զ���ֵ
	// Parameter: int color
	//************************************
	void iniColor(int color);

	//************************************
	// Method:    reverseFriendEnemy
	// FullName:  Map::reverseFriendEnemy
	// Access:    public 
	// Returns:   void
	// Qualifier: ת��friendColor �� enemyColor
	//��Ҫ��Ϊ�˸�defValue��ֵ
	//************************************
	void reverseFriendEnemy();

	//************************************
	// Method:    getNum
	// FullName:  Map::getNum
	// Access:    public 
	// Returns:   int
	// Qualifier: ����ض�������ѷ�������
	// Parameter: Chess ce
	// Parameter: int dir
	//************************************
	int getNum(Chess ce,int dir);

	//************************************
	// Method:    outputChess
	// FullName:  Map::outputChess
	// Access:    public 
	// Returns:   void
	// Qualifier: ������ӵ������Ϣ
	// Parameter: Chess ce
	//************************************
	void outputChess(Chess ce);

	//************************************
	// Method:    getNext
	// FullName:  Map::getNext
	// Access:    public 
	// Returns:   Chess
	// Qualifier: ��ȡ��ǰλ�����ӷ���һ������
	// Parameter: Chess ce
	// Parameter: int dir
	//************************************
	Chess getNext(Chess ce, int dir);

	//************************************
	// Method:    getPrev
	// FullName:  Map::getPrev
	// Access:    public 
	// Returns:   Chess
	// Qualifier: ��ȡ��ǰλ�����ӵ�ǰһ������
	// Parameter: Chess ce
	// Parameter: int dir
	//************************************
	Chess getPrev(Chess ce, int dir);

	//************************************
	// Method:    getChess
	// FullName:  Map::getChess
	// Access:    public 
	// Returns:   Chess
	// Qualifier: ͨ�������ȡ���̸�λ�õ���Ϣ
	//д��ŷ�������Ǹ����ﺯ��...
	// Parameter: int x
	// Parameter: int y
	//************************************
	Chess getChess(int x,int y);

	void outputOneDVector(std::vector<Chess> ce);
	void outputTwoDVector(std::vector<std::vector<Chess>> ce);

	//************************************
	// Method:    countLinkFive
	// FullName:  Map::countLinkFive
	// Access:    public 
	// Returns:   int
	// Qualifier: ��countLinkFive()Ϊ����ͳ������ce�����ⷽ��
	//���Ϳ���λ�ã����Ϳ��ܳ�������5�ĸ�����ʹ��ʱ���뱣֤��λ����������ɫ
	//�ͼ�����ɫһ�£�����Ҫ����friendColor������
	// Parameter: Chess ce
	//************************************
	int countLinkFive(Chess ce);
	int countLiveFour(Chess ce);
	int countRushFour(Chess ce);
	int countLiveThree(Chess ce);
	int countSleepThree(Chess ce);
	int countLiveTwo(Chess ce);
	int countSleepTwo(Chess ce);
private:
	//************************************
	// Method:    getChessChain
	// FullName:  Map::getChessChain
	// Access:    private 
	// Returns:   std::vector<std::vector<Chess>>
	// Qualifier: ��ȡ�ĸ�����ĳ���Ϊn,λ��Ϊloc��������
	// Parameter: Chess ce
	// Parameter: int n
	// Parameter: int loc
	//************************************
	std::vector<std::vector<Chess>> getChessChain(Chess ce,int n,int loc);
	//--getChessChain()������ĺ���Ҫ����ʹ��
	//--getChessChain()�������ĵ�������
	//Ȼ������������Ҫ�ֱ�ͨ������������жϺ���
	int linkFive(std::vector<std::vector<Chess>> ce,int n);
	int liveFour(std::vector<std::vector<Chess>> ce,int n);
	int rushFour(std::vector<std::vector<Chess>> ce,int n);
	int liveThree(std::vector<std::vector<Chess>> ce,int n);
	int sleepThree(std::vector<std::vector<Chess>> ce,int n);
	int liveTwo(std::vector<std::vector<Chess>> ce,int n);
	int sleepTwo(std::vector<std::vector<Chess>> ce,int n);
	//	|�ɵ������ӣ���ȡһά
	//	|��һά����ȡ��ά	
	//	|�Ӷ��𲽼�������жϵĸ���
	int linkFive(std::vector<Chess> ce,int n);
	int liveFour(std::vector<Chess> ce,int n);
	int rushFour(std::vector<Chess> ce,int n);
	int liveThree(std::vector<Chess> ce,int n);
	int sleepThree(std::vector<Chess> ce,int n);
	int liveTwo(std::vector<Chess> ce,int n);
	int sleepTwo(std::vector<Chess> ce,int n);

	int linkFive(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int rushFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int rushFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6,Chess ce7);
	int liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4);
	int liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int sleepTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int sleepTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);

	//************************************
	// Method:    fourChain
	// FullName:  Map::fourChain
	// Access:    private 
	// Returns:   std::vector<Chess>
	// Qualifier: ��fourChainΪ����˵��һ�¸ú���������
	//��������Ϊ4����ǰ�հ�λΪce,����Ϊdir���հ�λλ��Ϊloc��������
	//������������ֳ����߽磬���߸���loc��������������n���᷵��һ����������
	//��������ֻ��һ��Ԫ�أ���isBoundry��true���⣬��������ȫ��ERROR���Ӷ������ж�
	// Parameter: Chess ce ��ǰ���ӵ���Ϣ�����ڱ��жϵĿհ����ӣ�
	// Parameter: int dir �����������ĸ�����
	// Parameter: int loc ��ǰ�������������е�λ��
	//************************************
	std::vector<Chess> fourChain(Chess ce, int dir, int loc);
	std::vector<Chess> fiveChain(Chess ce, int dir, int loc);
	std::vector<Chess> sixChain(Chess ce, int dir, int loc);
	std::vector<Chess> sevenChain(Chess ce, int dir, int loc);

	//�����߸������Ķ����ǣ�λ��λ��one��two~seven������ce,����䷽��Ϊdir������Ϊn��������
	std::vector<Chess> inDirOne(Chess ce,int n,int dir);
	std::vector<Chess> inDirTwo(Chess ce,int n,int dir);
	std::vector<Chess> inDirThree(Chess ce,int n,int dir);
	std::vector<Chess> inDirFour(Chess ce,int n,int dir);
	std::vector<Chess> inDirFive(Chess ce,int n,int dir);
	std::vector<Chess> inDirSix(Chess ce,int n,int dir);
	std::vector<Chess> inDirSeven(Chess ce,int n,int dir);


	Chess upNext(Chess ce);
	Chess downNext(Chess ce);
	Chess leftNext(Chess ce);
	Chess rightNext(Chess ce);
	Chess leftUpNext(Chess ce);
	Chess rightUpNext(Chess ce);
	Chess leftDownNext(Chess ce);
	Chess rightDownNext(Chess ce);

	int getLayNum(Chess ce);
	int getStandNum(Chess ce);
	int getMainNum(Chess ce);
	int getViceNum(Chess ce);

	int up(Chess ce);
	int down(Chess ce);
	int left(Chess ce);
	int right(Chess ce);
	int leftUp(Chess ce);
	int rightUp(Chess ce);
	int leftDown(Chess ce);
	int rightDown(Chess ce);

	std::string defineToString(int code);
	std::string boolToString(bool flag);
	//************************************
	// Method:    getErrorChess
	// FullName:  Map::getErrorChess
	// Access:    private 
	// Returns:   Chess
	// Qualifier: ��ȡһ������ȫ��ERROR(��isBoundry��true),������
	//����һЩ�����Ĵ��󷵻�ֵ
	//************************************
	Chess getErrorChess();

	
	//************************************
	// Method:    chainIsOk
	// FullName:  Map::chainIsOk
	// Access:    private 
	// Returns:   bool
	// Qualifier: һά�������ȫ�����Ǳ߽�
	// Parameter: std::vector<Chess> ce
	//************************************
	bool chainOneDIsOk(std::vector<Chess> ce);

	//************************************
	// Method:    chainIsOK
	// FullName:  Map::chainIsOK
	// Access:    private 
	// Returns:   bool
	// Qualifier: ��ά����ֻҪ��һ��ok������
	// Parameter: std::vector<std::vector<Chess>> vce
	//************************************
	bool chainIsOK(std::vector<std::vector<Chess>> vce);
};

