#pragma once
#pragma once
#include "ObjectBase.h"
#include"CommonClass.h"

#define EFFECT_MAX 16
class C_HitBox;

class C_Effect :public ObjectBase
{
public:
	//仮置き

	//Vector2 slash_1, slash_2; //通常攻撃の当たり判定の範囲(slash1:左下,slash2:右下)
	//int slashrange = 30; //通常攻撃の範囲(溜めるほど伸びる)

	//Vectorクラス
	unsigned int BoxColor = RED;//表示箱の色


	C_Effect();
	C_Effect(int);
	~C_Effect();
	void Process();
	void Draw();
	void Init();
	void Exit();
	//各状態
	//条件式
	int mumi = 0;
	int anime_n = 1;
	int aniframe[32];
	//int mumii = 0;
							 //C_HitBox *hitbox[PLAYER_HITBOX_MAX]; 
	C_HitBox *hisbox_slash;//近接攻撃用のヒットボックスポインタ

	static int total;//totalはいままでそのオブジェクトがいくつ生成されたか
	static bool exi[EFFECT_MAX];//nullptrでも代用可かも
	static void AllProcess();
	static void AllDraw();

	static void AllDelete();
	static int Make();
	static void Delete(int);
	static int GetObject_n();

	int playerid;//0..1P 1..2P
	int direction; // 1..右 -1..左
	int state;

	int lifetime;//エフェクトの寿命
	C_HitBox *hitbox;//当たり判定のポインタ
	int arynum;//当たり判定の番号
	//状態
	int x;
protected:
	static int object_n;//
private:

};
extern C_Effect *effect[EFFECT_MAX];
