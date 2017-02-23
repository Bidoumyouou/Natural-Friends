#include "Player.h"
#include"ObjectList.h"
#include <DxLib.h>
#include "GV.h"
#include"key.h"
#include"Camera.h"
#include <math.h>
#include "HitBox.h"
#include"anime.h"
#include "GameMgr.h"
#include"View.h"
#include"Effect.h"
#include"main.h"
//////////////////////
//派生クラスPlayer
//・プロジェクトに追加したのち
//GameMgr.cppにインクルードすれば動く(はず)
//includeファイルの循環参照で困ったら
//ヘッダファイルでクラスの前方宣言を
//includeの代わりに用いるべし
//・コピーした後はGameMgr::ObjectProcessに<クラス名>::AllProcess()を
//書き入れる(Drawも同様、ついでに必要ならAllDelete()も)
///////////////////////

//基底クラスのint引数付きのものと同じタイミングで呼ぶために
//不要に見えるイニシャライザを持つ
C_Effect::C_Effect(int arynum) : ObjectBase(arynum) {
	exi[arraynum] = true;
	object_n++;
	id = total;
	total++;
	///////////////
}



C_Effect::~C_Effect() {
	///////////////
	exi[arraynum] = false;
	object_n--;
}

void C_Effect::Init() {
	//画像のあてはめ
	state = hitbox->Hitmode;
	arynum = hitbox->arraynum;
	switch (state) {
	case SLASH:Graph = Player_Graph[0][4]; break;
	case SHOT:Graph = Player_Graph[0][5]; break;
	}
	//座標の設定
	switch (state) {
	case SLASH:pos = hitbox->pos + hitbox->player->pos; break;
	case SHOT:pos.x = hitbox->player->pos.x; pos.x += SHOT_RANGE * hitbox->player->direction;
		pos.y = hitbox->abs_area.v[1].y - Graph.size.y / 2 ; break;
	}
	
	ObjectBase::SetUpperLeft();
	//寿命の設定
	lifetime = 20 + 60;
	
}

void C_Effect::Exit()
{
	
}






void C_Effect::Process() {
	if (!initflag) { ObjectBase::Init(); Init(); initflag = true; }
	ObjectBase::Process();
	//hitboxが生きてる限り座標を更新



	//近接だったら親がいなくなったら消える
	if (state == H_SLASH) {
		if (hitbox != nullptr && C_HitBox::exi[arynum] == true) {
			//pos = hitbox->pos + hitbox->player->pos;
			if (hitbox->player->direction == 1) {
				//右向き（画像ハンドル通り）
				pos = hitbox->abs_area.v[1];
				pos.y -= abs(hitbox->abs_area.v[1].y - hitbox->abs_area.v[0].y) / 2;
				direction = 1;
			}
			else {
				pos = hitbox->abs_area.v[0];
				direction = -1;
				pos.y += abs(hitbox->abs_area.v[1].y - hitbox->abs_area.v[0].y) / 2;

			}
			
		}
		if (hitbox == nullptr || C_HitBox::exi[arynum] != true) {
			deleteflag = true;
		}
	}
	//遠距離だったら寿命に応じて消える
	if (state == H_SHOT) {
		if (hitbox != nullptr && C_HitBox::exi[arynum] == true) {
			if (hitbox->area.v[0].y != hitbox->area.v[1].y) {
				//画像を噴出してる方に書き換える
				Graph.Handle = Player_Graph[0][6].Handle;
			}
		}
		if (lifetime <= t) {
			deleteflag = true;
		}
	}
}



void C_Effect::Draw() {
	if (state == H_SLASH) {
		DrawRotaGraph(pos.x - Camera.UpperLeft_pos.x, pos.y - Camera.UpperLeft_pos.y, 1.0, 0, Graph.Handle, 1, -direction);
	}
	if (state == H_SHOT) {
		DrawRotaGraph(pos.x - Camera.UpperLeft_pos.x, pos.y - Camera.UpperLeft_pos.y, 1.0, 0, Graph.Handle, 1, 0);
	}
}

//クラスのProcessを一括で動かす静的メンバ関数
void C_Effect::AllProcess() {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (C_Effect::exi[i]) {
			if (C_Effect::exi[i] == true) {
				effect[i]->Process();
			}if (effect[i]->deleteflag == true) {
				C_Effect::Delete(i);
				effect[i] = nullptr;
			}
		}
	}
}

//クラスのDrawを一括で動かす静的メンバ関数
void C_Effect::AllDraw(){
	for (int i = 0; i < EFFECT_MAX; i++){
		if (C_Effect::exi[i]) {
			if (C_Effect::exi[i] == true)
				effect[i]->Draw();
		}
		
	}
}

//インスタンスの作成
int C_Effect::Make() {
	for (int i = 0; i < object_n + 1; i++) {
		if (C_Effect::exi[i] == 0) {
			effect[i] = new C_Effect(i);
			return i;
		}
	}
}

//インスタンスの削除
void C_Effect::Delete(int i) {
	if (C_Effect::object_n > 0) {
		delete effect[i];
	}
}

//インスタンスの全削除
void C_Effect::AllDelete() {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (C_Player::exi[i] == true) {
			delete effect[i];
		}
	}
}



int C_Effect::GetObject_n() {
	return object_n;
}
int C_Effect::total = 0;
int C_Effect::object_n = 0;//静的メンバ変数の実体
bool C_Effect::exi[EFFECT_MAX] = {};
C_Effect* effect[EFFECT_MAX];

//////////////////////////////
//クラス未習得者向けCips
//・クラスは構造体を拡張したもので
//変数のほかに関数をいくつか持てる(メンバ変数、メンバ関数)
//(ProcessやDrawなどは実際にそうなっている)
//・クラスのメンバ関数内では内部のメンバ変数、関数を特に意識せず使える
//ex: メンバ変数に HP が入っているなら HP = 114514 
//・クラス外部から利用するときは ->(アロー) でオブジェクトを指定する
//ex 外部からplayerオブジェクトのHPを参照するときは
//player->HP = 0;
//HitCheck()関数を呼ぶなら
//player->HitCheck()
//(追加で)
//・staticで宣言されてるメンバを参照するときは
//Playerクラスが　static TotalAttack　のばあい
//Player::TotalAttack = 60
//となる
//
///////////////////////////////