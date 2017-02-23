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
//�h���N���XPlayer
//�E�v���W�F�N�g�ɒǉ������̂�
//GameMgr.cpp�ɃC���N���[�h����Γ���(�͂�)
//include�t�@�C���̏z�Q�Ƃō�������
//�w�b�_�t�@�C���ŃN���X�̑O���錾��
//include�̑���ɗp����ׂ�
//�E�R�s�[�������GameMgr::ObjectProcess��<�N���X��>::AllProcess()��
//���������(Draw�����l�A���łɕK�v�Ȃ�AllDelete()��)
///////////////////////

//���N���X��int�����t���̂��̂Ɠ����^�C�~���O�ŌĂԂ��߂�
//�s�v�Ɍ�����C�j�V�����C�U������
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
	//�ǂ�������player�Ȃ̂�
	playerid = arraynum;
	//��������
	if (arraynum == 0)
		direction = 1;
	else
		direction = -1;
	//���W�����Ŏw��
	if (arraynum == 0) {
		pos.Set(640 - 100, 400 - 60);
	}
	if (arraynum == 1) {
		pos.Set(640 + 100, 400 - 60);
	}

	Graph = P_Graph[0];

	//���u��
	//slash_1.Set(-20, -20); slash_2.Set(20, 20);
	test.Set2p(100, 100, 200, 200);
	//�A�j���[�V�����̏�����
	anime_n = 3;//�e�L�����ɍ��킹�Ē���
	for (int i = 0; i < anime_n; i++) {
		aniframe[i] = 8;
	}
	aniframe[0] = 8;
	aniframe[1] = 3;
	aniframe[2] = 8;
	Pre_State = DEFAULT;
	Main_State = DEFAULT;
	Next_State = DEFAULT;
	//������W�̃Z�b�g
	ObjectBase::SetUpperLeft();

	//�h��̂����蔻��
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
	  //�v���p�ɍ�����W�����߂�
		Vector2 v1; v1.x = pos.x - (Graph.size.x / 2); v1.y = pos.y - (Graph.size.y / 2);
		//�ǂ��������ւ͍s���Ȃ�
		if (v1.x < 0) {
			return false;
		}
		//���肩����ȏ㗣��Ȃ�Ȃ�
		if ((abs(pos.x - player[1]->pos.x) + PLAYERWIDTH) < WINDOW_X)
			return true;
		else
			return false;

	}
	else if (playerid == 1) {
		//�v���p�ɉE�����W�����߂�
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



//HitBox�C���X�^���X�̍쐬(x1,y1:HitBox�̍�����W x2,y2:HitBox�̉E�����W)
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
	//�q�b�g�{�b�N�X�̎�ނɍ��킹�čU�������̕ύX
	switch (State) {
	case H_SLASHCHARGE:hitbox_p[State]->AttackStatus.Set(SLASH_A, SLASH_BACK); break;
	case H_SHOT:hitbox_p[State]->AttackStatus.Set(SHOT_A, SHOT_BACK); break;
	}
	return ary;
}

void C_Player::Process() {
	if (!initflag) { ObjectBase::Init(); Init(); initflag = true; }
	ObjectBase::Process();
	//HitBox�ŎQ�Ƃ���p�̃v���C���[���W
	m_GameMgr->p_pos[playerid] = pos;
	//objectbase����ڐ�
	state_t++;
	if (Next_State != Main_State)
		state_t = 0;
	//��ԑJ��
	Pre_State = Main_State;
	Main_State = Next_State;

	//�Q�[���J�n����͍s���s��
	//if (t < START_FRAME)
	//	return;

	//�v���C���[�̏�Ԃɍ��킹�Ċ֐������s
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

		//�X�e�[�W�[����o�Ȃ��悤�ɁB 1�h�b�g�P�ʂ̃Y�����邩��
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
	//Z�L�[�������ꂽ��
	if (Pad[playerid].Button[PAD_Z] == 1 /*&& Main_State == DEFAULT*/) {
		//�ʏ�U���p�̂����蔻����쐬
		//int p = MakeHitBox(slash_1, slash_2, H_SLASHCHARGE);
		Vector2 V1, V2;
		V1.Set(0, -(SLASH_HEIGHT / 2));
		V2.Set(0, (SLASH_HEIGHT / 2));
		int p = MakeHitBox(V1, V2, H_SLASHCHARGE);
		HitBox[p]->Next_Hitmode = H_SLASHCHARGE;
		//State�̕ύX
		Next_State = SLASHCHARGE;
	}
	//X�L�[�������ꂽ��
	if (Pad[playerid].Button[PAD_X] == 1) {
		//�������U���p�̂����蔻����쐬
		Vector2 V1, V2;
		V1.Set(-(SHOT_WIDE / 4), 0);
		V2.Set((SHOT_WIDE / 4), 0);
		int p = MakeHitBox(V1, V2, H_SHOT);
		HitBox[p]->Next_Hitmode = H_SHOT;
		//State�̕ύX
		Next_State = SHOT;
		//�G�t�F�N�g�̂��Ԃ������Ƃ��쐬
		p = C_Effect::Make();
		effect[p]->hitbox = hitbox_p[H_SHOT];
	}

	//C�L�[�������ꂽ��
	if (Pad[playerid].Button[PAD_C] == 1) {
		//�J�E���^�[�p�̂����蔻����쐬
		Vector2 V = { 0, 0 };
		int p = MakeHitBox(V, V, H_COUNTER);
		HitBox[p]->Next_Hitmode = H_COUNTER;
		//State�̕ύX
		Next_State = COUNTER;
	}

}

void C_Player::SlashCharge()
{

	if (hitbox_exi[H_SLASHCHARGE] == true && hitbox_p[H_SLASHCHARGE]->Next_Hitmode == H_NONE)
		Next_State = DEFAULT;
	//���̃��[�h�̊�
	//Z�L�[�������ꂽ��
	if (Pad[playerid].Button[PAD_Z] == 0) {
		Next_State = SLASH;
		//�q�b�g�{�b�N�X�̏�Ԃ�ς���
		hitbox_p[H_SLASH] = hitbox_p[H_SLASHCHARGE];
		hitbox_p[H_SLASHCHARGE]->Next_Hitmode = H_SLASH;
		//�G�t�F�N�g�̂��Ԃ������Ƃ��쐬
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
	//�J�E���^�[�ł���t���O���I�t��
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
	//��U�J�E���^�[�󂯂��Ƃ��̃X�^���Ƃ��Ďg�p
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
	//�_���[�W���󂯂�
	if (!dameged) {
		dameged = true;
		HP -= DamegeStatus.power;
	}
	//����Ƀm�b�N�o�b�N
	if (IsRange()) {
		pos.x -= direction * DamegeStatus.backspeed;
		back += 8;
		if (!IsRange()) {
			pos.x += direction * DamegeStatus.backspeed;

		}
	}
	//�m�b�N�o�b�N����߂����
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
		//�����ȊO�̃v���C���[��
		if (player[i]->playerid != playerid) {
			//�ԍ����ɂ������
			while (abs(player[i]->pos.x - pos.x) < PLAYERWIDTH/2) {
				//�i�s�����ɉ����o��
				player[i]->pos.x += direction;
			}
			//�����o�����v���C���[���J�����͈͂��яo���Ă�����
			while (!player[i]->IsRange()) {
				//��яo���������݂��ɖ߂�B
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
	//���u���̐����`�`��
	if (DEBUG) {
		DrawBox(UpperLeft_pos.x - Camera.UpperLeft_pos.x, UpperLeft_pos.y, UpperLeft_pos.x + Graph.size.x - Camera.UpperLeft_pos.x, UpperLeft_pos.y + Graph.size.y, BoxColor, 1);
		//��Ԃ�\��
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

//�N���X��Process���ꊇ�œ������ÓI�����o�֐�
void C_Player::AllProcess() {
	for (int i = 0; i < total; i++) {
		if (C_Player::exi[i]) {
			if (C_Player::exi[i] == true)
				player[i]->Process();
		}
	}
}

//�N���X��Draw���ꊇ�œ������ÓI�����o�֐�
void C_Player::AllDraw() {
	for (int i = 0; i < total; i++) {
		if (C_Player::exi[i]) {
			if (C_Player::exi[i] == true)
				player[i]->Draw();
		}
	}
}

//�C���X�^���X�̍쐬
void C_Player::Make() {
	for (int i = 0; i < object_n + 1; i++) {
		if (C_Player::exi[i] == 0) {
			player[i] = new C_Player(i);
			return;
		}
	}
}

//�C���X�^���X�̍폜
void C_Player::Delete(int i) {
	if (C_Player::object_n > 0) {
		delete player[i];
	}
}

//�C���X�^���X�̑S�폜
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
int C_Player::object_n = 0;//�ÓI�����o�ϐ��̎���
bool C_Player::exi[PLAYER_MAX] = {};
C_Player* player[PLAYER_MAX];

//////////////////////////////
//�N���X���K���Ҍ���Cips
//�E�N���X�͍\���̂��g���������̂�
//�ϐ��̂ق��Ɋ֐������������Ă�(�����o�ϐ��A�����o�֐�)
//(Process��Draw�Ȃǂ͎��ۂɂ����Ȃ��Ă���)
//�E�N���X�̃����o�֐����ł͓����̃����o�ϐ��A�֐�����Ɉӎ������g����
//ex: �����o�ϐ��� HP �������Ă���Ȃ� HP = 114514 
//�E�N���X�O�����痘�p����Ƃ��� ->(�A���[) �ŃI�u�W�F�N�g���w�肷��
//ex �O������player�I�u�W�F�N�g��HP���Q�Ƃ���Ƃ���
//player->HP = 0;
//HitCheck()�֐����ĂԂȂ�
//player->HitCheck()
//(�ǉ���)
//�Estatic�Ő錾����Ă郁���o���Q�Ƃ���Ƃ���
//Player�N���X���@static TotalAttack�@�̂΂���
//Player::TotalAttack = 60
//�ƂȂ�
//
///////////////////////////////