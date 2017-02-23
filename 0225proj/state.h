#ifndef DEF_STATE_H
#define DEF_STATE_H

void stateMgr();

enum E_MAINGAMESTATE{
	DEF,
	TITLE,
	E_MGSTATE_STAGEINIT,
	E_MGSTATE_GAMESTART,//�Q�[���J�n�G�t�F�N�g
	GAME,
	E_MGSTATE_GAMEEND,//�Q�[���I�����G�t�F�N�g
	RESULT,//�X�R�A�\��(�N���A�摜�\���A�R���e�B�j���[�`�F�b�N�\��)
	E_MGSTATE_END,//�Q�[���̏I������
	SELECT,
};

extern E_MAINGAMESTATE G_MainGameState;
extern E_MAINGAMESTATE G_Pre_GameState;
extern E_MAINGAMESTATE G_Next_GameState;
#endif