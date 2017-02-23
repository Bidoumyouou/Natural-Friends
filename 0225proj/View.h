#pragma once
#include "CommonClass.h"
#include "Resource.h"
//オブジェクト以外のゲームの見た目を一括管理するクラス
class GameMgr;

class C_View {
public:
	C_Graph Back_G;//背景画像
	C_Graph Timer_G;
	C_Graph HpFrame_G;
	C_Graph HpBar_G;
	C_Font OldEng_F;
	void init();
	void Draw();
	void Draw2();
	void Process();

	GameMgr *mgr;
};

extern C_View View;