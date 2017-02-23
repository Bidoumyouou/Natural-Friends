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
	//�摜�̂��Ă͂�
	state = hitbox->Hitmode;
	arynum = hitbox->arraynum;
	switch (state) {
	case SLASH:Graph = Player_Graph[0][4]; break;
	case SHOT:Graph = Player_Graph[0][5]; break;
	}
	//���W�̐ݒ�
	switch (state) {
	case SLASH:pos = hitbox->pos + hitbox->player->pos; break;
	case SHOT:pos.x = hitbox->player->pos.x; pos.x += SHOT_RANGE * hitbox->player->direction;
		pos.y = hitbox->abs_area.v[1].y - Graph.size.y / 2 ; break;
	}
	
	ObjectBase::SetUpperLeft();
	//�����̐ݒ�
	lifetime = 20 + 60;
	
}

void C_Effect::Exit()
{
	
}






void C_Effect::Process() {
	if (!initflag) { ObjectBase::Init(); Init(); initflag = true; }
	ObjectBase::Process();
	//hitbox�������Ă������W���X�V



	//�ߐڂ�������e�����Ȃ��Ȃ����������
	if (state == H_SLASH) {
		if (hitbox != nullptr && C_HitBox::exi[arynum] == true) {
			//pos = hitbox->pos + hitbox->player->pos;
			if (hitbox->player->direction == 1) {
				//�E�����i�摜�n���h���ʂ�j
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
	//������������������ɉ����ď�����
	if (state == H_SHOT) {
		if (hitbox != nullptr && C_HitBox::exi[arynum] == true) {
			if (hitbox->area.v[0].y != hitbox->area.v[1].y) {
				//�摜�𕬏o���Ă���ɏ���������
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

//�N���X��Process���ꊇ�œ������ÓI�����o�֐�
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

//�N���X��Draw���ꊇ�œ������ÓI�����o�֐�
void C_Effect::AllDraw(){
	for (int i = 0; i < EFFECT_MAX; i++){
		if (C_Effect::exi[i]) {
			if (C_Effect::exi[i] == true)
				effect[i]->Draw();
		}
		
	}
}

//�C���X�^���X�̍쐬
int C_Effect::Make() {
	for (int i = 0; i < object_n + 1; i++) {
		if (C_Effect::exi[i] == 0) {
			effect[i] = new C_Effect(i);
			return i;
		}
	}
}

//�C���X�^���X�̍폜
void C_Effect::Delete(int i) {
	if (C_Effect::object_n > 0) {
		delete effect[i];
	}
}

//�C���X�^���X�̑S�폜
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
int C_Effect::object_n = 0;//�ÓI�����o�ϐ��̎���
bool C_Effect::exi[EFFECT_MAX] = {};
C_Effect* effect[EFFECT_MAX];

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