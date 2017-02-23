#pragma once
#include"ObjectBase.h"
#include"Player.h"
#include"CommonClass.h"
#include"Character.h"

#define HITBOX_MAX 64

#define SLASH_MODE 0//0..�U���̒������R�i�K�ɕ�����@1..�U���̒������`���[�W���Ԃɔ�Ⴓ����

//���W��HitBox�𐶂ݏo����Player�̍��W�Ƒ���
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
	//�e���
	void None();
	void Defence();//�h�䑤����
	void SlashCharge(); //�ʏ�U������ 
	void Slash(); //�ʏ�U��
	void Shot(); //�������U��
	void Counter(); //�J�E���^�[

	C_Player *player;
	
	static int total;//total�͂��܂܂ł��̃I�u�W�F�N�g�������������ꂽ��
	static bool exi[PLAYER_MAX];//nullptr�ł���p����
	static void AllProcess();
	static void AllDraw();
	static void AllDelete();
	static void Make();
	static int Make2();
	static void Delete(int);
	static int GetObject_n();

	Square area; //�x�N�g���ɂ��͈͎w��(���S�_��0,0�Ƃ���)
	Square abs_area;//�����蔻��̂���ꏊ�̐�Βl
	Vector2 p_pos; //�v���C���[�̍��W��Vector2�����o�[�Ƃ��ĕێ�
	int p_id;//�v���C���[��id
	//�U���p
	C_AttackStatus AttackStatus;
	int slash_t;//�ߐڂ̃`���[�W����
	int slash_level;//�ߐڂ̍U�����x�� 0~2
	//int slash_speed = SLASH_SPEED;
	int slash_state = 0;//0..�L�т�@1..�k��
	void HitCheck();//�U�������������Ƃ��̏���
	//�h��p
	bool isHit = false;//�U���𓖂Ă���true�ɂȂ�
	int reactstate[3];//�h��A�J�E���^�[�̍ۂɔ������邠���蔻��̎�ނ�ێ�
	
	unsigned int BoxColor;
protected:
	static int object_n;//
private:
};
extern int p_gid[64];
extern C_HitBox *HitBox[HITBOX_MAX];