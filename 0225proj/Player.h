#pragma once
#include"ObjectBase.h"
#include"CommonClass.h"
#include"Character.h"

#define PLAYER_MAX 64
#define PLAYER_HITBOX_MAX 64

#define PLAYER1 0
#define PLAYER2 1


#define MAX_HP 3000

//仮置き
#define PLAYERWIDTH 130         //プレイヤー大きさ
#define PLAYERHEIGHT 130
#define PLAYERSPEED 4           //1フレーム当たりの移動スピード
#define BACKWIDTH 1280          //背景大きさ
#define BACKHEIGHT 480



//カウンター受けたときに硬直するフレーム
#define COUNTER_STUN 16
class C_HitBox;

class C_Player :public ObjectBase
{
public:
	//仮置き
	
	//Vector2 slash_1, slash_2; //通常攻撃の当たり判定の範囲(slash1:左下,slash2:右下)
	//int slashrange = 30; //通常攻撃の範囲(溜めるほど伸びる)

	//Vectorクラス
	unsigned int BoxColor = RED;//表示箱の色
	

	C_Player();
	C_Player(int);
	~C_Player();
	void Process();
	void Draw();
	void Init();
	void Exit();
	//指定した状態のHitBoxインスタンス作成　作られたHitBoxの配列番号を返す。
	int MakeHitBox(Vector2, Vector2, E_HitMode);
	//各状態
	void Default();
	void SlashCharge(); //通常攻撃溜め 
	void Slash(); //通常攻撃
	void Shot(); //遠距離攻撃
	void Counter(); //カウンター
	void Stun();
	void Damege();
	//処理関数
	void Push_Out();
	//条件式
	int mumi = 0;
	int anime_n = 1;
	int aniframe[32];
	//int mumii = 0;
	bool IsRange();//プレイヤー間の距離が一定以内か
	bool CanMove();//移動可能か
	bool CanMakeHitBox();//HitBoxを作れる状態か
	bool hitbox_exi[H_HitMode_N];//指定の状態のヒットボックスが存在しているか。
	//

	//C_HitBox *hitbox[PLAYER_HITBOX_MAX]; 
	C_HitBox *hisbox_slash;//近接攻撃用のヒットボックスポインタ
	C_HitBox *hisbox_shot;//遠距離攻撃用のヒットボックスポインタ
	C_HitBox *hisbox_counter;//カウンター用のヒットボックスポインタ
	C_HitBox *hisbox_defence;//防御用のヒットボックスポインタ
	C_HitBox* hitbox_p[H_HitMode_N];//
	
	static int total;//totalはいままでそのオブジェクトがいくつ生成されたか
	static bool exi[PLAYER_MAX];//nullptrでも代用可かも
	static void AllProcess();
	static void AllDraw();
	static void AllDelete();
	static void Make();
	static void Delete(int);
	static int GetObject_n();

	int playerid;//0..1P 1..2P
	int direction; // 1..右 -1..左

	int HP = MAX_HP;//プレイヤーの体力
	bool dameged;//true
	Square test;
	//状態
	STATE Pre_State = DEFAULT;
	STATE Main_State = DEFAULT;
	STATE Next_State = DEFAULT;
	bool Counterattack;
	C_AttackStatus DamegeStatus;//受けた攻撃のステータス
	int back;//現在のノックバック量
	int stanframe;//スタンする時間

	CHARACTER CHARANUM;
	S_Status Chara;
protected:
	static int object_n;//
private:

};
extern C_Player *player[PLAYER_MAX];
