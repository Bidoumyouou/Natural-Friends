#pragma once
#include"ObjectBase.h"
#include"Player.h"
#include"CommonClass.h"
#include"Character.h"

#define HITBOX_MAX 64

#define SLASH_MODE 0//0..攻撃の長さを３段階に分ける　1..攻撃の長さをチャージ時間に比例させる

//座標はHitBoxを生み出したPlayerの座標と相対
class C_HitBox : public ObjectBase {
public:		
	C_HitBox(int);
	~C_HitBox();
	void Process();
	void Draw();
	void Init();
	void Exit();
	int state_t = 0;;
	E_HitMode Pre_Hitmode;
	E_HitMode Hitmode;
	E_HitMode Next_Hitmode;
	//各状態
	void None();
	void Defence();//防御側判定
	void SlashCharge(); //通常攻撃溜め 
	void Slash(); //通常攻撃
	void Shot(); //遠距離攻撃
	void Counter(); //カウンター

	C_Player *player;
	
	static int total;//totalはいままでそのオブジェクトがいくつ生成されたか
	static bool exi[PLAYER_MAX];//nullptrでも代用可かも
	static void AllProcess();
	static void AllDraw();
	static void AllDelete();
	static void Make();
	static int Make2();
	static void Delete(int);
	static int GetObject_n();

	Square area; //ベクトルによる範囲指定(中心点を0,0とする)
	Square abs_area;//当たり判定のある場所の絶対値
	Vector2 p_pos; //プレイヤーの座標をVector2メンバーとして保持
	int p_id;//プレイヤーのid
	//攻撃用
	C_AttackStatus AttackStatus;
	int slash_t;//近接のチャージ時間
	int slash_level;//近接の攻撃レベル 0~2
	//int slash_speed = SLASH_SPEED;
	int slash_state = 0;//0..伸びる　1..縮む
	void HitCheck();//攻撃が当たったときの処理
	//防御用
	bool isHit = false;//攻撃を当てたらtrueになる
	int reactstate[3];//防御、カウンターの際に反応するあたり判定の種類を保持
	
	unsigned int BoxColor;
protected:
	static int object_n;//
private:
};
extern int p_gid[64];
extern C_HitBox *HitBox[HITBOX_MAX];