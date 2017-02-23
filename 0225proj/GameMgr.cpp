#include "GameMgr.h"
#include "Dxlib.h"
#include "key.h"

#include "class.h"
#include "Player.h"
//�ȉ��̓e�X�g�ȊO�ł͕s�v
#include"ObjectList.h"
#include"Camera.h"
#include"View.h"
#include"HitBox.h"

#include"Effect.h"
//////////////////////
//GameMgr�N���X
//�����̃N���X���g��Ȃ��v���O�����ł����Ƃ����
//�u�Q�[���̃��C�����[�h��While���[�v���v�ɑ�������B
//�Q�[���I�[�o�[�ɂȂ����Ƃ��Ȃǂ�
//G_Next_GameState = RESULT �ȂǂƏ�����
//���U���g�Ɉڍs�ł���B
//
//
///////////////////////
GameMgr::GameMgr(){
	timerinit();
	Camera.init();
	View.init();
	View.mgr = this;//View�N���X��
	stagesize = View.Back_G.size.x;//�t�B�[���h�̃T�C�Y�i���݂͉摜�T�C�Y�Ɉˑ��j
	t = 0;
	time = 99;
	PlaySoundMem(Battle_Sound.Handle, DX_PLAYTYPE_LOOP);
}

GameMgr::~GameMgr(){
	

}

void GameMgr::Process(){
	Camera.Process();
	View.Process();

	//���Ԍo�߂𑪂�
	t++;
	if (t >= START_FRAME && t % 60 == 0) time--;
	if (time < 0) time = 0;

	Object_Process();
	//T�������ꂽ��N���X�ꔭ�쐬
	if (sKey[KEY_INPUT_T].var == 1){
		C_Player::Make();
	}

}

void GameMgr::Object_Process()
{
	
	C_Player::AllProcess();
	C_HitBox::AllProcess();
	C_Effect::AllProcess();
	//deleteflag��true�ɂ���HitBox���폜����
}

void GameMgr::Draw(){
	Camera.Draw();
	View.Draw();
	Object_Draw();
	View.Draw2();
	if (t == 60) PlaySoundMem(Ready_Sound.Handle, DX_PLAYTYPE_BACK);
	if (t == 180) PlaySoundMem(Start_Sound.Handle, DX_PLAYTYPE_BACK);

	if (t >= 61 && t <=120) DrawGraph(280, 120, Ready_Graph.Handle, TRUE);
	if (t >= 170 && t <= 200) DrawGraph(280, 120, Start_Graph.Handle, TRUE);

	clsDx();
	printfDx("t = %d, time = %d", t, time);
}

void GameMgr::Object_Draw()
{
	C_Player::AllDraw();
	C_HitBox::AllDraw();
	C_Effect::AllDraw();
}

void GameMgr::Init(){
	//PlaySoundMem(G_MUSIC_00, DX_PLAYTYPE_BACK, true);
	//�e�X�g�p�̃I�u�W�F�N�g�̐ݒu
	player[0] = new C_Player(0);
	player[1] = new C_Player(1);

	//�X�e�[�^�X�ύX�_(��)
	Status[HONO].slash_A = HONO_SLASH_A;

	//�X�e�[�^�X�ύX�_(��)

	//�X�e�[�^�X�ύX�_(��)


}
void GameMgr::Finish(){
	//���[�h�J�ڎ��ɍ폜�������I�u�W�F�N�g��
	//�폜�����菉���������肷��
	C_Player::AllDelete();
	C_HitBox::AllDelete();

	StopSoundMem(Battle_Sound.Handle);
}

GameMgr* m_GameMgr;