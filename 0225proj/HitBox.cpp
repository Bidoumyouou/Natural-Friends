#include"HitBox.h"
#include"Camera.h"
#include"Player.h"
#include"GameMgr.h"
#include"math.h"

C_HitBox::C_HitBox(int arynum) : ObjectBase(arynum) {
	exi[arraynum] = true;
	object_n++;
	id = total;
	total++;
	///////////////
}

C_HitBox::~C_HitBox()
{
	exi[arraynum] = false;
	object_n--;
}

void C_HitBox::Process()
{
	ObjectBase::Process();
	if (!initflag) { Init(); initflag = 1; }

	p_id = 0;

	//状態変化の瞬間に
	if (Hitmode != Next_Hitmode) {
		state_t = 0;
	}
	else { state_t++; }
	//状態変化
	Pre_Hitmode = Hitmode;
	Hitmode = Next_Hitmode;
	player->hitbox_exi[Pre_Hitmode] = false;
	player->hitbox_exi[Hitmode] = true;
	if (!initflag) { ObjectBase::Init(); Init(); initflag = true; }
	//状態によって分岐
	switch (Hitmode) {
	case H_SLASH:Slash(); break;
	case H_SLASHCHARGE:SlashCharge(); break;
	case H_DEFENCE:Defence(); break;
	case H_SHOT:Shot(); break;
		//case H_NONE:None(); break;
	case H_COUNTER:Counter(); break;
	case H_NONE:None(); break;
	}


	//森絶対座標と相対座標の統一

	if (Hitmode > 0 && Hitmode <= H_HitMode_N - 1) {
		//プレイヤーのposを保存
		if (player != nullptr) {
			p_pos = m_GameMgr->p_pos[p_gid[arraynum]];
		}
		if (Hitmode == H_SHOT) {
			//プレイヤーの座標に依存しない
			//abs_area.Set2p(area.v[0].x , area.v[0].y , area.v[1].x , area.v[1].y);
			abs_area.Set2p(abs_area.v[0].x, abs_area.v[0].y, abs_area.v[1].x, abs_area.v[1].y);
		}
		else {
			//プレイヤーの座標に依存
			//abs_area.v[0] = area.v[0] + p_pos;
			//abs_area.v[1] = area.v[1] + p_pos;
			abs_area.Set2p(area.v[0].x + p_pos.x, area.v[0].y + p_pos.y, area.v[1].x + p_pos.x, area.v[1].y + p_pos.y);
		}
	}
	//不正なステータスになったらdeletefagをオン
	if (!(Hitmode >= 0 && Hitmode < H_HitMode_N)) {
		deleteflag = true;
	}
}

void C_HitBox::HitCheck() {

}

void C_HitBox::Draw()
{
	switch (Hitmode) {
	case H_SLASHCHARGE:BoxColor = RED; break;
	case H_SLASH:BoxColor = BLUE; break;
	case H_SHOT:BoxColor = GREEN; break;
	case H_COUNTER:BoxColor = YELLOW; break;
	case H_DEFENCE:BoxColor = PURPLE; break;
	default:BoxColor = PURPLE; break;
	}

	//DrawBox(pos.x - Camera.UpperLeft_pos.x + player->pos.x, pos.y + player->pos.y, pos.x + player->pos.x + 50 - Camera.UpperLeft_pos.x, pos.y + player->pos.y + 50, BoxColor, 1);
	if (DEBUG) {
		//DrawBox(area.v[0].x - Camera.UpperLeft_pos.x + player->pos.x, area.v[0].y + player->pos.y, area.v[1].x - Camera.UpperLeft_pos.x + player->pos.x, area.v[1].y + player->pos.y, BoxColor, 1);
		DrawBox(abs_area.v[0].x - Camera.UpperLeft_pos.x, abs_area.v[0].y, abs_area.v[1].x - Camera.UpperLeft_pos.x, abs_area.v[1].y, BoxColor, 1);
	}

}

void C_HitBox::Init()
{
	//攻撃のステータスの仮置き
	switch (Next_Hitmode) {
	case H_SLASHCHARGE: H_SLASH:AttackStatus.Set(SLASH_A, SLASH_BACK); break;
	case H_SHOT:AttackStatus.Set(SHOT_A, SHOT_BACK); break;
	default:AttackStatus.Set(0, 0); break;
	}
	p_gid[arraynum] = player->playerid;
	//HitBoxインスタンスを呼び出したPlayerインスタンスのポインタを記憶
	for (int i = 0; i < PLAYER_HITBOX_MAX; i++) {
		//if (player->hitbox[i] == nullptr) {
		//	player->hitbox[i] = this;
		//}
		//pos.Set(200, 100);
	}
}

void C_HitBox::Exit()
{
}

void C_HitBox::None()
{
	//自動的に破棄
	deleteflag = true;
	//C_HitBox::Delete(arraynum);
}



void C_HitBox::Defence()
{

	if (Pre_Hitmode == H_NONE) {
		area.v[0].x = -(PLAYERWIDTH / 6);
		area.v[1].x = +(PLAYERWIDTH / 6);
		area.v[0].y = -(PLAYERHEIGHT / 6); //プレイヤーの中心点座標分下げる
		area.v[1].y = +(PLAYERHEIGHT / 6);
		area.Set2p(area.v[0], area.v[1]);
	}
	if (player->Counterattack) {
		reactstate[0] = H_SHOT;
		reactstate[1] = -1;
		reactstate[2] = -1;
	}
	/*else if (player->Main_State == COUNTER) {
		reactstate[0] = H_SHOT;
		reactstate[1] = -1;
		reactstate[2] = -1;

	}*/
	else {
		reactstate[0] = H_SHOT;
		reactstate[1] = H_SLASH;
		reactstate[2] = -1;
	}

	//範囲内に攻撃が入ったら
	//全てのヒットボックスに対して
	for (int i = 0; i < HITBOX_MAX; i++) {
		if (HitBox[i] == nullptr) { continue; }
		//ヒットボックスの種類が攻撃系だったら
		if (HitBox[i]->Hitmode == reactstate[0] || HitBox[i]->Hitmode == reactstate[1] || HitBox[i]->Hitmode == reactstate[2]) {
			//ヒットボックスが相手プレイヤーのものだったら
			if (HitBox[i]->player->playerid != player->playerid) {
				//戻っている腕には攻撃判定無し
				if (HitBox[i]->slash_state != 1)
					//攻撃を仕掛けたヒットボックスのポインタを入手
					//ヒットボックスが座標内に入っていたら
					for (int j = 0; j < 4; j++) {
						//当たり判定ガバいので直す
						if (HitBox[i]->abs_area.inSquare(abs_area.v[j])) {
							HitBox[i]->isHit = true;
							player->Next_State = DAMEGE;
							//ダメージステータス
							player->DamegeStatus = HitBox[i]->AttackStatus;
							break;

						}
					}
			}
		}
	}


}

void C_HitBox::SlashCharge()
{
	slash_t++;
	//チャージの長さに応じたあたり判定の大きさの変更
	if (slash_t >= 0 && slash_t < player->Chara.slash_chrge_time) {
		slash_level = 0;
	}
	else if (slash_t >= player->Chara.slash_chrge_time && slash_t < player->Chara.slash_chrge_time * 2) {
		slash_level = 1;

	}
	else {
		slash_level = 2;
	}
}

void C_HitBox::Slash()
{
	if (player->Counterattack && state_t == 0) {
		slash_level = 2;
		AttackStatus.Set(COUNTER_A, COUNTER_BACK);
	}
	int i;
	if (player->direction == 1)
		i = 1;
	else
		i = 0;

	//長さが貯めた量の規定以上になったら
	if ((slash_level + 1) * player->Chara.slash_lange_unit < abs(area.v[i].x)) {
		slash_state = 1;
	}
	if (isHit == true) {
		slash_state = 1;
	}
	//実際にあたり判定を伸ばす
	if (slash_state == 0) {
		Vector2 tmp = area.v[i];
		tmp.x += player->Chara.slash_speed * player->direction;
		//pos_v.Set2p(pos_v.v[0], tmp);
		if (i == 1)
			area.Set2p(area.v[0], tmp);
		else if (i == 0)
			area.Set2p(tmp, area.v[1]);
	}
	//縮める
	if (slash_state == 1) {
		Vector2 tmp = area.v[i];
		tmp.x -= (player->Chara.slash_speed / 2) * player->direction;
		//pos_v.Set2p(pos_v.v[0], tmp);
		if (i == 1)
			area.Set2p(area.v[0], tmp);
		else if (i == 0)
			area.Set2p(tmp, area.v[1]);
	}

	if (player->direction == 1) {
		if (area.v[1].x < 0) {
			Next_Hitmode = H_NONE;
		}
	}
	else if (player->direction == -1) {
		if (area.v[0].x > 0) {
			Next_Hitmode = H_NONE;
		}
	}


}

void C_HitBox::Shot()
{
	if (Pre_Hitmode == H_NONE) {
		area.v[0].x += SHOT_RANGE * player->direction;
		area.v[1].x += SHOT_RANGE * player->direction;
		area.v[0].y += PLAYERHEIGHT / 2; //プレイヤーの中心点座標分下げる
		area.v[1].y += PLAYERHEIGHT / 2;
		area.Set2p(area.v[0], area.v[1]);
		abs_area.Set2p(area.v[0].x + p_pos.x, area.v[0].y + p_pos.y, area.v[1].x + p_pos.x, area.v[1].y + p_pos.y);
	}

	/*if (area.v[0].y > -SHOT_HEIGHT) {
		area.v[0].y -= SHOT_SPEED;
		area.Set2p(area.v[0], area.v[1]);
	}*/
	if (state_t < SHOT_WAIT) {
		;
	}
	else if (state_t == SHOT_WAIT) {
		area.v[0].y -= (SHOT_HEIGHT);
		area.Set2p(area.v[0], area.v[1]);
		abs_area.Set2p(area.v[0].x + p_pos.x, area.v[0].y + p_pos.y, area.v[1].x + p_pos.x, area.v[1].y + p_pos.y);
	}
	else if (state_t < SHOT_WAIT + SHOT_TIME) {
		if (isHit)
			Next_Hitmode = H_NONE;;
	}
	else {
		Next_Hitmode = H_NONE;
	}
}

void C_HitBox::Counter()
{
	/*if (state_t < COUNTER_WAIT) {
		if(player->Next_State == DAMEGE)
			Next_Hitmode = H_NONE;
	}*/
	if (state_t == 0) {
		area.v[0].x -= (PLAYERWIDTH / 6) + SHOT_SPEED;
		area.v[1].x += (PLAYERWIDTH / 6) + SHOT_SPEED;
		area.v[0].y -= (PLAYERHEIGHT / 6) + SHOT_SPEED; //プレイヤーの中心点座標分下げる
		area.v[1].y += (PLAYERHEIGHT / 6) + SHOT_SPEED;
		area.Set2p(area.v[0], area.v[1]);
	}
	else if (state_t < COUNTER_TIME) {
		;
	}
	else {
		Next_Hitmode = H_NONE;
		player->Next_State = STUN;
		player->stanframe = COUNTER_TIME;
	}
	//近接攻撃が入ってきたときの条件

	//範囲内に攻撃が入ったら
	//全てのヒットボックスに対して
	for (int i = 0; i < HITBOX_MAX; i++) {
		if (HitBox[i] == nullptr) { continue; }
		//ヒットボックスの種類が射撃だったら
		if (C_HitBox::exi[i] && HitBox[i]->Hitmode == H_SLASH) {
			//ヒットボックスが相手プレイヤーのものだったら
			if (HitBox[i]->player->playerid != player->playerid) {
				//攻撃を仕掛けたヒットボックスのポインタを入手
				//ヒットボックスが座標内に入っていたら
				for (int j = 0; j < 4; j++) {
					//当たり判定ガバいので直す
					if (HitBox[i]->abs_area.inSquare(abs_area.v[j])) {
						HitBox[i]->isHit = true;
						//HitBox[i]->player->Next_State = STUN;
						//ダメージステータス(無意味)
						HitBox[i]->player->DamegeStatus = AttackStatus;
						//プレイヤーの状態をSLASHにする
						player->Next_State = SLASH;
						//カウンター攻撃用のあたり判定を作成
						Vector2 V1, V2;
						V1.Set(0, -(SLASH_HEIGHT / 2));
						V2.Set(0, (SLASH_HEIGHT / 2));
						int p = player->MakeHitBox(V1, V2, H_SLASH);
						HitBox[p]->Next_Hitmode = H_SLASH;
						//Stateの変更
						player->Next_State = SLASH;
						slash_level = 2;
						player->Counterattack = true;
						Next_Hitmode = H_NONE;
						HitBox[i]->Next_Hitmode = H_NONE;
						HitBox[i]->player->Next_State = STUN;
						HitBox[i]->player->stanframe = COUNTER_STUN;
						break;

					}
				}
			}
		}
	}
}

void C_HitBox::AllProcess()
{
	for (int i = 0; i < total; i++) {
		if (C_HitBox::exi[i]) {
			if (C_HitBox::exi[i] == true) {
				HitBox[i]->Process();
			}
			if (HitBox[i]->deleteflag == true) {
				C_HitBox::Delete(i);
				HitBox[i] = nullptr;
			}

		}
	}

}

void C_HitBox::AllDraw()
{
	for (int i = 0; i < total; i++) {
		if (C_HitBox::exi[i]) {
			if (C_HitBox::exi[i] == true)
				HitBox[i]->Draw();
		}
	}
}

void C_HitBox::AllDelete()
{
	for (int i = 0; i < PLAYER_MAX; i++) {
		if (C_HitBox::exi[i] == true) {
			delete HitBox[i];
		}
	}
}

void C_HitBox::Make()
{
	for (int i = 0; i < object_n + 1; i++) {
		if (C_HitBox::exi[i] == 0) {
			HitBox[i] = new C_HitBox(i);
			return;
		}
	}
}

int C_HitBox::Make2()
{
	for (int i = 0; i < object_n + 1; i++) {
		if (C_HitBox::exi[i] == 0) {
			HitBox[i] = new C_HitBox(i);
			return i;
		}
	}
}

void C_HitBox::Delete(int i)
{
	if (C_HitBox::object_n > 0) {
		delete HitBox[i];
	}
}

int C_HitBox::GetObject_n()
{
	return 0;
}

int C_HitBox::total = 0;
int C_HitBox::object_n = 0;//静的メンバ変数の実体
bool C_HitBox::exi[PLAYER_MAX] = {};


int p_gid[64];
C_HitBox *HitBox[64];

