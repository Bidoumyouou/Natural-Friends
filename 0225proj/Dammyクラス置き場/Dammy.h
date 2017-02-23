#pragma once
#include "ObjectBase.h"
#include"CommonClass.h"

#define DAMMY_MAX 64
class Dammy :public ObjectBase 
{
public:
	//Vectorクラス
	Vector2 pos;
	
	Dammy();
	Dammy(int);
	~Dammy();
	void Process();
	void Draw();
	static int total;//totalはいままでそのオブジェクトがいくつ生成されたか
	static bool exi[DAMMY_MAX];//nullptrでも代用可かも
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
