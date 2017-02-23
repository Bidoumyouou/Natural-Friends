#pragma once
#include "ObjectBase.h"
#include"CommonClass.h"

#define DAMMY_MAX 64
class Dammy :public ObjectBase 
{
public:
	//Vector�N���X
	Vector2 pos;
	
	Dammy();
	Dammy(int);
	~Dammy();
	void Process();
	void Draw();
	static int total;//total�͂��܂܂ł��̃I�u�W�F�N�g�������������ꂽ��
	static bool exi[DAMMY_MAX];//nullptr�ł���p����
	static void AllProcess();
	static void AllDraw();
	static void AllDelete();
	static void Make();
	static void Delete(int);
	static int GetObject_n();
protected:
	static int object_n;//
};
extern Dammy *dammy[DAMMY_MAX];
