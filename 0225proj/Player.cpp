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
C_Player::C_Player(int arynum) : ObjectBase(arynum) {
	exi[arraynum] = true;
	object_n++;
	id = total;
	total++;
	///////////////
}



C_Player::~C_Player() {
	///////////////
	exi[arraynum] = false;
	object_n--;
}

void C_Player::Init() {
	//どっち側のplayerなのか
	playerid = arraynum;
	//初期向き
	if (arraynum == 0)
		direction = 1;
	else
		direction = -1;
	//座標を仮で指定
	if (arraynum == 0) {
		pos.Set(640 - 100, 400 - 60);
	}
	if (arraynum == 1) {
		pos.Set(640 + 100, 400 - 60);
	}

	Graph = P_Graph[0];

	//仮置き
	//slash_1.Set(-20, -20); slash_2.Set(20, 20);
	test.Set2p(100, 100, 200, 200);
	//アニメーションの初期化
	anime_n = 3;//各キャラに合わせて調整
	for (int i = 0; i < anime_n; i++) {
		aniframe[i] = 8;
	}
	aniframe[0] = 8;
	aniframe[1] = 3;
	aniframe[2] = 8;
	Pre_State = DEFAULT;
	Main_State = DEFAULT;
	Next_State = DEFAULT;
	//左上座標のセット
	ObjectBase::SetUpperLeft();

	//防御のあたり判定
	Vector2 V, V2;
	V.Set(50, 50);
	V2.Set(0, 0);
	int p = MakeHitBox(V2, V, H_DEFENCE);


	for (int i = 0; i < H_HitMode_N; i++)
		hitbox_exi[i] = false;
	Vector2 V0 = { 0, 0 };
	//int p2 = MakeHitBox(V0, V0, H_DEFENCE);
	//HitBox[p2]->Next_Hitmode = H_DEFENCE;

	Chara = m_GameMgr->Status[HONO];
}

void C_Player::Exit()
{
}

bool C_Player::IsRange()
{

	if (playerid == 0) {
		/*
		  UpperLeft_pos.x = pos.x - (Graph.size.x / 2);
		  UpperLeft_pos.y = pos.y - (Graph.size.y / 2);
		  LowerRight_pos.x = UpperLeft_pos.x + Graph.size.x;
		  LowerRight_pos.y = UpperLeft_pos.y + Graph.size.y;
	  */
	  //計測用に左上座標を求める
		Vector2 v1; v1.x = pos.x - (Graph.size.x / 2); v1.y = pos.y - (Graph.size.y / 2);
		//壁より向こうへは行けない
		if (v1.x < 0) {
			return false;
		}
		//相手から一定以上離れなれない
		if ((abs(pos.x - player[1]->pos.x) + PLAYERWIDTH) < WINDOW_X)
			return true;
		else
			return false;

	}
	else if (playerid == 1) {
		//計測用に右下座標を求める
		Vector2 v2; v2.x = pos.x + (Graph.size.x / 2); v2.y = pos.y + (Graph.size.y / 2);
		if (v2.x > View.Back_G.size.x) {
			return false;
		}

		if ((abs(pos.x - player[0]->pos.x) + PLAYERWIDTH) < WINDOW_X)
			return true;
		else
			return false;
	}
	return true;
}

bool C_Player::CanMove()
{
	if (Main_State == DEFAULT || Main_State == SLASHCHARGE)
		return true;
	else
		return false;
}

bool C_Player::CanMakeHitBox()
{
	if (Main_State == DEFAULT)
		return true;
	else
		return false;
}



//HitBoxインスタンスの作成(x1,y1:HitBoxの左上座標 x2,y2:HitBoxの右下座標)
int C_Player::MakeHitBox(Vector2 _v0, Vector2 _v1, E_HitMode State) {
	int ary = C_HitBox::Make2();
	HitBox[ary]->player = this;
	HitBox[ary]->area.Set2p(_v0, _v1);
	HitBox[ary]->pos.x = (HitBox[ary]->area.v[0].x + HitBox[ary]->area.v[1].x) / 2;
	HitBox[ary]->pos.y = (HitBox[ary]->area.v[0].y + HitBox[ary]->area.v[1].y) / 2;
	//HitBox[arynum]->Next_State = State;
	switch (State) {
	case H_DEFENCE:hitbox_p[H_DEFENCE] = HitBox[ary]; break;
	case SLASHCHARGE:hitbox_p[H_SLASHCHARGE] = HitBox[ary]; break;
	case H_SLASH:hitbox_p[H_SLASH] = HitBox[ary]; break;
	case H_SHOT:hitbox_p[H_SHOT] = HitBox[ary]; break;
	case H_COUNTER:hitbox_p[H_COUNTER] = HitBox[ary]; break;
		//case SLASHCHARGE:hitbox_p[H_SLASHCHARGE] = HitBox[ary]; break;
		//case :hitbox_p[H_SLASHCHARGE] = HitBox[ary]; break;
	}
	hitbox_exi[State] = true;
	hitbox_p[State] = HitBox[ary];
	hitbox_p[State]->Next_Hitmode = State;

	hitbox_p[State]->p_id = playerid;
	//ヒットボックスの種類に合わせて攻撃特性の変更
	switch (State) {
	case H_SLASHCHARGE:hitbox_p[State]->AttackStatus.Set(SLASH_A, SLASH_BACK); break;
	case H_SHOT:hitbox_p[State]->AttackStatus.Set(SHOT_A, SHOT_BACK); break;
	}
	return ary;
}

void C_Player::Process() {
	if (!initflag) { ObjectBase::Init(); Init(); initflag = true; }
	ObjectBase::Process();
	//HitBoxで参照する用のプレイヤー座標
	m_GameMgr->p_pos[playerid] = pos;
	//objectbaseから移設
	state_t++;
	if (Next_State != Main_State)
		state_t = 0;
	//状態遷移
	Pre_State = Main_State;
	Main_State = Next_State;

	//ゲーム開始直後は行動不可
	//if (t < START_FRAME)
	//	return;

	//プレイヤーの状態に合わせて関数を実行
	switch (Main_State) {
	case DEFAULT:    Default(); break;
	case SLASHCHARGE:SlashCharge(); break;
	case SLASH:      Slash(); break;
	case SHOT: Shot(); break;
	case COUNTER:    Counter(); break;
	case STUN:       Stun(); break;
	case DAMEGE:     Damege(); break;
	}


	if (/*IsRange() && */CanMove()) {
		if (Pad[playerid].Right) {
			pos.x += PLAYERSPEED;
			while (!IsRange())
				pos.x--;
		}
		Push_Out();

		if (Pad[playerid].Left) {
			pos.x -= PLAYERSPEED;
			while (!IsRange()) {
				pos.x++;
			}
			Push_Out();
		}

		//ステージ端から出ないように。 1ドット単位のズレあるかも
		if (pos.x < 0 + (PLAYERWIDTH / 2)) {
			pos.x = (PLAYERWIDTH / 2);
		}
		else if (pos.x > BACKWIDTH - (PLAYERWIDTH / 2)) {
			pos.x = BACKWIDTH - (PLAYERWIDTH / 2);
		}

	}
	if (Pad[playerid].Button[PAD_Q]) {
		//m_GameMgr->G_Next_GameState
		G_Next_GameState = TITLE;
	}


}

void C_Player::Default() {
	//Zキーが押されたら
	if (Pad[playerid].Button[PAD_Z] == 1 /*&& Main_State == DEFAULT*/) {
		//通常攻撃用のあたり判定を作成
		//int p = MakeHitBox(slash_1, slash_2, H_SLASHCHARGE);
		Vector2 V1, V2;
		V1.Set(0, -(SLASH_HEIGHT / 2));
		V2.Set(0, (SLASH_HEIGHT / 2));
		int p = MakeHitBox(V1, V2, H_SLASHCHARGE);
		HitBox[p]->Next_Hitmode = H_SLASHCHARGE;
		//Stateの変更
		Next_State = SLASHCHARGE;
	}
	//Xキーが押されたら
	if (Pad[playerid].Button[PAD_X] == 1) {
		//遠距離攻撃用のあたり判定を作成
		Vector2 V1, V2;
		V1.Set(-(SHOT_WIDE / 4), 0);
		V2.Set((SHOT_WIDE / 4), 0);
		int p = MakeHitBox(V1, V2, H_SHOT);
		HitBox[p]->Next_Hitmode = H_SHOT;
		//Stateの変更
		Next_State = SHOT;
		//エフェクトのおぶじぇくとを作成
		p = C_Effect::Make();
		effect[p]->hitbox = hitbox_p[H_SHOT];
	}

	//Cキーが押されたら
	if (Pad[playerid].Button[PAD_C] == 1) {
		//カウンター用のあたり判定を作成
		Vector2 V = { 0, 0 };
		int p = MakeHitBox(V, V, H_COUNTER);
		HitBox[p]->Next_Hitmode = H_COUNTER;
		//Stateの変更
		Next_State = COUNTER;
	}

}

void C_Player::SlashCharge()
{

	if (hitbox_exi[H_SLASHCHARGE] == true && hitbox_p[H_SLASHCHARGE]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;
	//このモードの間
	//Zキーが離されたら
	if (Pad[playerid].Button[PAD_Z] == 0) {
		Next_State = SLASH;
		//ヒットボックスの状態を変える
		hitbox_p[H_SLASH] = hitbox_p[H_SLASHCHARGE];
		hitbox_p[H_SLASHCHARGE]->Next_Hitmode = H_SLASH;
		//エフェクトのおぶじぇくとを作成
		int p = C_Effect::Make();
		effect[p]->hitbox = hitbox_p[H_SLASHCHARGE];
	}
	//
	//if (HitBox[i]->state_t == 60) {
	//	slashrange = 60;
	//}
	//if (HitBox[i]->state_t == 120) {
	//	slashrange = 90;
	//}
}

void C_Player::Slash()
{
	//カウンターであるフラグをオフに
	Counterattack = false;
	if (hitbox_exi[H_SLASH] == true && hitbox_p[H_SLASH]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;
	/*if (state_t >= 8) {
		Next_State = STUN;
	}*/
	/*if (HitBox[i]->pos.x < slashrange)
		HitBox[i]->pos.x += 6;
	else
		HitBox[i]->Main_State = STUN;*/
}

void C_Player::Shot()
{
	if (hitbox_exi[H_SHOT] == true && hitbox_p[H_SHOT]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;
	/*if (state_t >= 8) {
		Next_State = STUN;
	}*/
}

void C_Player::Counter()
{
	if (hitbox_p[H_COUNTER]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;
	/*
	if (state_t >= 8) {
		Next_State = STUN;
	}*/
}

void C_Player::Stun()
{
	//一旦カウンター受けたときのスタンとして使用
	/*
	if (hitbox_exi[H_SLASH] == true && hitbox_p[H_SLASH]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;

	if (hitbox_exi[H_SHOT] == true && hitbox_p[H_SHOT]->Next_Hitmode == H_NONE)
		Next_State = DEFALT;

	if (hitbox_exi[H_COUNTER] == true && hitbox_p[H_COUNTER]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;
		*/

	if (state_t < stanframe)
		return;
	Next_State = DEFAULT;

}

void C_Player::Damege() {
	//printfDx("dd");
	//ダメージを受ける
	if (!dameged) {
		dameged = true;
		HP -= DamegeStatus.power;
	}
	//後方にノックバック
	if (IsRange()) {
		pos.x -= direction * DamegeStatus.backspeed;
		back += 8;
		if (!IsRange()) {
			pos.x += direction * DamegeStatus.backspeed;

		}
	}
	//ノックバックをやめる条件
	if (back >= DamegeStatus.nockback) {
		Next_State = DEFAULT;
		back = 0;
		dameged = false;
	}

}

void C_Player::Push_Out()
{/*
	if (hitbox_exi[H_DEFENCE]) {
		for (int i = 0; i < HITBOX_MAX; i++) {
			if (HitBox[i] == nullptr) { continue; }
			if (HitBox[i]->Hitmode == H_DEFENCE && HitBox[i]->player->playerid != playerid) {
				for (int j = 0; j < 4; j++) {
					while (HitBox[i]->abs_area.inSquare(hitbox_p[H_DEFENCE]->abs_area.v[j])) {
						HitBox[i]->player->pos.x += direction;
						HitBox[i]->abs_area.Set2p(HitBox[i]->area.v[0].x + HitBox[i]->player->pos.x, HitBox[i]->area.v[0].y + HitBox[i]->player->pos.y, HitBox[i]->area.v[1].x + HitBox[i]->player->pos.x, HitBox[i]->area.v[1].y + HitBox[i]->player->pos.y);
					}
					if (!HitBox[i]->player->IsRange()) {
						while (!HitBox[i]->player->IsRange()) {
							HitBox[i]->player->pos.x -= direction;
							HitBox[i]->abs_area.Set2p(HitBox[i]->area.v[0].x + HitBox[i]->player->pos.x, HitBox[i]->area.v[0].y + HitBox[i]->player->pos.y, HitBox[i]->area.v[1].x + HitBox[i]->player->pos.x, HitBox[i]->area.v[1].y + HitBox[i]->player->pos.y);
						}
						HitBox[i]->player->Push_Out();
					}
					while (!HitBox[i]->player->IsRange()) {
						HitBox[i]->player->pos.x += HitBox[i]->player->direction;
						pos.x += HitBox[i]->player->direction;
					}
				}
			}
		}
	}
	*/
	for (int i = 0; i < PLAYER_MAX; i++) {
		if (player[i] == nullptr) { continue; }
		//自分以外のプレイヤーが
		if (player[i]->playerid != playerid) {
			//間合いにいる限り
			while (abs(player[i]->pos.x - pos.x) < PLAYERWIDTH/2) {
				//進行方向に押し出す
				player[i]->pos.x += direction;
			}
			//押し出したプレイヤーがカメラ範囲を飛び出していたら
			while (!player[i]->IsRange()) {
				//飛び出した分お互いに戻る。
				pos.x -= direction;
				player[i]->pos.x -= direction;
			}
		}
		
	}

}

void C_Player::Draw() {
	switch (Main_State) {
	case DEFAULT:BoxColor = RED; break;
	case SLASHCHARGE:BoxColor = BLUE; break;
	case SLASH:BoxColor = GREEN; break;
	case SHOT:BoxColor = YELLOW; break;
	case COUNTER:BoxColor = PURPLE; break;
	case STUN:BoxColor = LIGHT_GREEN; break;
	case DAMEGE:BoxColor = BLACK; break;
	default:BoxColor = RED; break;
	}

	ObjectBase::Draw();
	//仮置きの正方形描画
	if (DEBUG) {
		DrawBox(UpperLeft_pos.x - Camera.UpperLeft_pos.x, UpperLeft_pos.y, UpperLeft_pos.x + Graph.size.x - Camera.UpperLeft_pos.x, UpperLeft_pos.y + Graph.size.y, BoxColor, 1);
		//状態を表示
		DrawFormatString(UpperLeft_pos.x - Camera.UpperLeft_pos.x, UpperLeft_pos.y, BLACK, "%d", Main_State);
	}

	int p_handle = AnimeFrame2(3, Graph.HandleArray, aniframe, &mumi, true);
	DrawRotaGraph(pos.x - Camera.UpperLeft_pos.x, pos.y, 1.0, 0.0, Graph.Handle, 1, playerid);

	/*
	if (playerid == 0) {
		DrawRotaGraph(pos.x - Camera.UpperLeft_pos.x, pos.y, 1.0, 0.0, Graph.Handle, 1, playerid);
		//DrawRotaGraph(pos.x - Camera.UpperLeft_pos.x, pos.y, 2.0, 0.0, p_handle, 1, playerid);
	}
	else {
		DrawRotaGraph(pos.x - Camera.UpperLeft_pos.x, pos.y, 2.0, 0.0, p_handle, 1, playerid);
	}
	*/
	DrawPixel(pos.x - Camera.UpperLeft_pos.x, pos.y, BLUE);
	//DrawBox(x, y, x + 100, y + 100, GetColor(255, 255, 255), 1);
	if (DEBUG) {
		DrawFormatString(pos.x - Camera.UpperLeft_pos.x, pos.y, BLUE, "ID = %d", id);
	}


}

//クラスのProcessを一括で動かす静的メンバ関数
void C_Player::AllProcess() {
	for (int i = 0; i < total; i++) {
		if (C_Player::exi[i]) {
			if (C_Player::exi[i] == true)
				player[i]->Process();
		}
	}
}

//クラスのDrawを一括で動かす静的メンバ関数
void C_Player::AllDraw() {
	for (int i = 0; i < total; i++) {
		if (C_Player::exi[i]) {
			if (C_Player::exi[i] == true)
				player[i]->Draw();
		}
	}
}

//インスタンスの作成
void C_Player::Make() {
	for (int i = 0; i < object_n + 1; i++) {
		if (C_Player::exi[i] == 0) {
			player[i] = new C_Player(i);
			return;
		}
	}
}

//インスタンスの削除
void C_Player::Delete(int i) {
	if (C_Player::object_n > 0) {
		delete player[i];
	}
}

//インスタンスの全削除
void C_Player::AllDelete() {
	for (int i = 0; i < PLAYER_MAX; i++) {
		if (C_Player::exi[i] == true) {
			delete player[i];
		}
	}
}



int C_Player::GetObject_n() {
	return object_n;
}
int C_Player::total = 0;
int C_Player::object_n = 0;//静的メンバ変数の実体
bool C_Player::exi[PLAYER_MAX] = {};
C_Player* player[PLAYER_MAX];

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