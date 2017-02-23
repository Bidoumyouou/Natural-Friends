#ifndef DEF_GAME_H
#define DEF_GAME_H
#include "Resource.h"
#include "state.h"
#include "StateBase.h"
#include "Character.h"
#include "Resource.h"
#define START_FRAME 181

//////////////////
//�^�C�g���A���C���A���U���g
//�ȊO�̏�Ԃ������������Ȃ�state.cpp�ɂ����Đ^�����Ēǉ����ׂ�
//////////////////

class GameMgr:public CSbase{
private:
	int typenum;
	int typeexi;
	void Object_Process();//�I�u�W�F�N�g�𓮂����֐�
	void Object_Draw();
	int stagesize;
public:
	GameMgr();
	~GameMgr();
	void Init();
	void Finish();
	void Process();
	void Draw();
	int t;
	int time;
	void AllObjectProcess();
	void AllObjectDraw();
	Vector2 p_pos[2];
	S_Status Status[CHARACTER_N];
	//
};

extern GameMgr* m_GameMgr;
#endif