#pragma once
#include"ObjectBase.h"
#include"CommonClass.h"
#include"Character.h"

#define PLAYER_MAX 64
#define PLAYER_HITBOX_MAX 64

#define PLAYER1 0
#define PLAYER2 1


#define MAX_HP 3000

//���u��
#define PLAYERWIDTH 130         //�v���C���[�傫��
#define PLAYERHEIGHT 130
#define PLAYERSPEED 4           //1�t���[��������̈ړ��X�s�[�h
#define BACKWIDTH 1280          //�w�i�傫��
#define BACKHEIGHT 480



//�J�E���^�[�󂯂��Ƃ��ɍd������t���[��
#define COUNTER_STUN 16
class C_HitBox;

class C_Player :public ObjectBase
{
public:
	//���u��
	
	//Vector2 slash_1, slash_2; //�ʏ�U���̓����蔻��͈̔�(slash1:����,slash2:�E��)
	//int slashrange = 30; //�ʏ�U���͈̔�(���߂�قǐL�т�)

	//Vector�N���X
	unsigned int BoxColor = RED;//�\�����̐F
	

	C_Player();
	C_Player(int);
	~C_Player();
	void Process();
	void Draw();
	void Init();
	void Exit();
	//�w�肵����Ԃ�HitBox�C���X�^���X�쐬�@���ꂽHitBox�̔z��ԍ���Ԃ��B
	int MakeHitBox(Vector2, Vector2, E_HitMode);
	//�e���
	void Default();
	void SlashCharge(); //�ʏ�U������ 
	void Slash(); //�ʏ�U��
	void Shot(); //�������U��
	void Counter(); //�J�E���^�[
	void Stun();
	void Damege();
	//�����֐�
	void Push_Out();
	//������
	int mumi = 0;
	int anime_n = 1;
	int aniframe[32];
	//int mumii = 0;
	bool IsRange();//�v���C���[�Ԃ̋��������ȓ���
	bool CanMove();//�ړ��\��
	bool CanMakeHitBox();//HitBox�������Ԃ�
	bool hitbox_exi[H_HitMode_N];//�w��̏�Ԃ̃q�b�g�{�b�N�X�����݂��Ă��邩�B
	//

	//C_HitBox *hitbox[PLAYER_HITBOX_MAX]; 
	C_HitBox *hisbox_slash;//�ߐڍU���p�̃q�b�g�{�b�N�X�|�C���^
	C_HitBox *hisbox_shot;//�������U���p�̃q�b�g�{�b�N�X�|�C���^
	C_HitBox *hisbox_counter;//�J�E���^�[�p�̃q�b�g�{�b�N�X�|�C���^
	C_HitBox *hisbox_defence;//�h��p�̃q�b�g�{�b�N�X�|�C���^
	C_HitBox* hitbox_p[H_HitMode_N];//
	
	static int total;//total�͂��܂܂ł��̃I�u�W�F�N�g�������������ꂽ��
	static bool exi[PLAYER_MAX];//nullptr�ł���p����
	static void AllProcess();
	static void AllDraw();
	static void AllDelete();
	static void Make();
	static void Delete(int);
	static int GetObject_n();

	int playerid;//0..1P 1..2P
	int direction; // 1..�E -1..��

	int HP = MAX_HP;//�v���C���[�̗̑�
	bool dameged;//true
	Square test;
	//���
	STATE Pre_State = DEFAULT;
	STATE Main_State = DEFAULT;
	STATE Next_State = DEFAULT;
	bool Counterattack;
	C_AttackStatus DamegeStatus;//�󂯂��U���̃X�e�[�^�X
	int back;//���݂̃m�b�N�o�b�N��
	int stanframe;//�X�^�����鎞��

	CHARACTER CHARANUM;
	S_Status Chara;
protected:
	static int object_n;//
private:

};
extern C_Player *player[PLAYER_MAX];
