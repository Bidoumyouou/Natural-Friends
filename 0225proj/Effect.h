#pragma once
#pragma once
#include "ObjectBase.h"
#include"CommonClass.h"

#define EFFECT_MAX 16
class C_HitBox;

class C_Effect :public ObjectBase
{
public:
	//���u��

	//Vector2 slash_1, slash_2; //�ʏ�U���̓����蔻��͈̔�(slash1:����,slash2:�E��)
	//int slashrange = 30; //�ʏ�U���͈̔�(���߂�قǐL�т�)

	//Vector�N���X
	unsigned int BoxColor = RED;//�\�����̐F


	C_Effect();
	C_Effect(int);
	~C_Effect();
	void Process();
	void Draw();
	void Init();
	void Exit();
	//�e���
	//������
	int mumi = 0;
	int anime_n = 1;
	int aniframe[32];
	//int mumii = 0;
							 //C_HitBox *hitbox[PLAYER_HITBOX_MAX]; 
	C_HitBox *hisbox_slash;//�ߐڍU���p�̃q�b�g�{�b�N�X�|�C���^

	static int total;//total�͂��܂܂ł��̃I�u�W�F�N�g�������������ꂽ��
	static bool exi[EFFECT_MAX];//nullptr�ł���p����
	static void AllProcess();
	static void AllDraw();

	static void AllDelete();
	static int Make();
	static void Delete(int);
	static int GetObject_n();

	int playerid;//0..1P 1..2P
	int direction; // 1..�E -1..��
	int state;

	int lifetime;//�G�t�F�N�g�̎���
	C_HitBox *hitbox;//�����蔻��̃|�C���^
	int arynum;//�����蔻��̔ԍ�
	//���
	int x;
protected:
	static int object_n;//
private:

};
extern C_Effect *effect[EFFECT_MAX];
