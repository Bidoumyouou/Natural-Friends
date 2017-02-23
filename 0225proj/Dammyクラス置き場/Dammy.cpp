#include "Dammy.h"
#include"ObjectList.h"
#include <DxLib.h>
#include "GV.h"

//////////////////////
//�h���N���XDammy
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
Dammy::Dammy(int arynum) : ObjectBase(arynum) {
	exi[arraynum] = true;
	object_n++;
	id = total;
	total++;
	///////////////
}



Dammy::~Dammy(){
	///////////////
	exi[arraynum] = false;
	object_n--;
}

void Dammy::Process(){
	ObjectBase::Process();
}

void Dammy::Draw(){
	ObjectBase::Process();
	//���u���̐����`�`��
	DrawBox(x, y, x + 100, y + 100, GetColor(255, 255, 255), 1);
	DrawFormatString(x, y, BLUE, "ID = %d", id);
}

//�N���X��Process���ꊇ�œ������ÓI�����o�֐�
void Dammy::AllProcess(){
	for (int i = 0; i < total; i++){
		if (Dammy::exi[i]){
			if (Dammy::exi[i] == true)
			dammy[i]->Process();
		}
	}
}

//�N���X��Draw���ꊇ�œ������ÓI�����o�֐�
void Dammy::AllDraw(){
	for (int i = 0; i < total; i++){
		if (Dammy::exi[i]){
			if(Dammy::exi[i] == true)
			dammy[i]->Draw();
		}
	}
}

//�C���X�^���X�̍쐬
void Dammy::Make(){
	for (int i = 0; i < object_n + 1; i++){
		if (Dammy::exi[i] == 0){
			dammy[i] = new Dammy(i);
			return;
		}
	}
}

//�C���X�^���X�̍폜
void Dammy::Delete(int i){
	if (Dammy::object_n > 0){
		delete dammy[i];
	}
}

//�C���X�^���X�̑S�폜
void Dammy::AllDelete() {
	for (int i = 0; i < DAMMY_MAX;i++) {
		if (Dammy::exi[i] == true) {
			delete dammy[i];
		}
	}
}
int Dammy::GetObject_n(){
	return object_n;
}

int Dammy::total = 0;
int Dammy::object_n = 0;//�ÓI�����o�ϐ��̎���
bool Dammy::exi[DAMMY_MAX] = {};
Dammy* dammy[DAMMY_MAX];

//////////////////////////////
//�N���X���K���Ҍ���Cips
//�E�N���X�͍\���̂��g���������̂�
//�ϐ��̂ق��Ɋ֐������������Ă�(�����o�ϐ��A�����o�֐�)
//(Process��Draw�Ȃǂ͎��ۂɂ����Ȃ��Ă���)
//�E�N���X�̃����o�֐����ł͓����̃����o�ϐ��A�֐�����Ɉӎ������g����
//ex: �����o�ϐ��� HP �������Ă���Ȃ� HP = 114514 
//�E�N���X�O�����痘�p����Ƃ��� ->(�A���[) �ŃI�u�W�F�N�g���w�肷��
//ex �O������dammy�I�u�W�F�N�g��HP���Q�Ƃ���Ƃ���
//dammy->HP = 0;
//HitCheck()�֐����ĂԂȂ�
//dammy->HitCheck()
//(�ǉ���)
//�Estatic�Ő錾����Ă郁���o���Q�Ƃ���Ƃ���
//Dammy�N���X���@static TotalAttack�@�̂΂���
//Dammy::TotalAttack = 60
//�ƂȂ�
//
///////////////////////////////