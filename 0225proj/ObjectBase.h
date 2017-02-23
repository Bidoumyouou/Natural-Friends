#pragma once
#define OBJECT_MAX 1024 
#include"CommonClass.h"
#include"Resource.h"
//////////////////////
//���N���XObjectBase
//�E���ׂĂ̔h���N���X�� Process Draw AllProcess 
// AllDraw Make Delete ���I�[�o�[���C�h����ׂ�
//�E�ȒP�ɔh���N���X�������@��Player.h,Player.cpp��
//�v���W�F�N�g�ɒǉ�����Player��C�ӂ̃I�u�W�F�N�g����
//�u�����邱�Ƃł���B
//
//
///////////////////////

///////////////////////
//�ꉞ���ʂ̃����o�ϐ��Ƃ��č��W��t(���܂�Ă���̃t���[����)�������Ă��邪
//�p�ɂɊO������Q�Ƃ���v�f�͎��O�ɐ􂢏o����
//���N���X��h���N���X�ɒǉ��������
//���L����ׂ�
///////////////////////

//�U���̓���
class C_AttackStatus {
public:
	int power;//�U����
	int nockback;//�m�b�N�o�b�N
	int backspeed;//�m�b�N�o�b�N�̂����ҁ[��
	void Set(int _power, int _nockback, int _backspeed = 8) {
		power = _power;
		nockback = _nockback;
		backspeed = _backspeed;
	}
};

enum STATE {
	DEFAULT,           //�f�t�H���g
	SLASHCHARGE,  //�ʏ�U������
	SLASH,        //�ʏ�U��
	SHOT,    //�������U��
	COUNTER,       //�J�E���^�[
	STUN,          //�d��
	DAMEGE,        //��_���[�W
	STATE_N,
};

enum E_HitMode {
	H_NONE,
	H_SLASHCHARGE,
	H_SLASH,
	H_SHOT,
	H_DEFENCE,
	H_COUNTER,
	H_HitMode_N,
};

class ObjectBase
{
public:
	//static�̓N���X���ł���������ϐ��ŕ\��(�ÓI�����o�ϐ�)
	ObjectBase();
	ObjectBase(int);
	~ObjectBase();

	virtual void Process();
	virtual void Draw();
	virtual void Init();
	virtual void Exit();
	static void AllProcess();
	static void AllDraw();
	static void Make();
	static void Delete(int);
	
	int arraynum;//���̃I�u�W�F�N�g����������Ă�����̂̔z��ԍ�(ID�ł͂Ȃ�)
	int global_id;//�I�u�W�F�N�g�̒ʂ��ԍ�
	int id;//�I�u�W�F�N�g��ޕʂ̒ʂ��ԍ�(������)
/////////////////////////
//�ȏ�,�@�\������̂ɕK�{�̃����o
/////////////////////////
	Vector2 pos;
	Vector2 draw_pos;//�`��p�̍��W(�K�v�Ȃ�g��)
	C_Graph Graph;//�摜�n���h�����N���X
	//C_Graph G_Handle2;//�摜�n���h���\��
	int z;//�`��̏���
	int t;//��������Ă���̎���
	int state_t;//���̏�ԂɂȂ��Ă���̎���
	Vector2 UpperLeft_pos;	//�`����W�̍���//����������ĂȂ�Vector2�ϐ��͊댯
	Vector2 LowerRight_pos; //�`����W�̉E��
	
	void SetUpperLeft();
	bool deleteflag;//���ꂪtrue�ɂȂ�Ə��ł���
private:
	bool CompState(); //���̏�Ԃƍ��̏�Ԃ��Ⴄ�Ȃ�true
protected:
	bool initflag = false;
	static int global_object_n;//
	static int global_total;

};
extern ObjectBase* Object[OBJECT_MAX];
