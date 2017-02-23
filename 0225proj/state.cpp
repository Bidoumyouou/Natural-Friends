#include"state.h"

#include"main.h"

#include"Result.h"

E_MAINGAMESTATE G_MainGameState;
E_MAINGAMESTATE G_Pre_GameState;
E_MAINGAMESTATE G_Next_GameState;

bool CompState = false;//���̏�Ԃƍ��̏�Ԃ��Ⴄ�Ȃ�true(�����p���ď�Ԃ��ς�����u�Ԃ�\��)

void ProcessMgr();
void DrawMgr();

void stateMgr(){
	
	ProcessMgr();
	//void MidMgr();
	DrawMgr();
	//void EffectMgr();
	if (G_MainGameState != G_Next_GameState){
		CompState = true;
	}
	else{
		CompState = false;
	}
	G_Pre_GameState = G_MainGameState;
	G_MainGameState = G_Next_GameState;
}

void ProcessMgr(){
	//��Ԃ��ς��u�ԂȂ炱����(Init�ƑO������ԃN���X�̍폜)
	if (CompState == true){
		switch (G_MainGameState){
		case TITLE:m_title = new Title();   m_title->Init(); break;
		case SELECT:m_select = new Select();   m_select->Init(); break;
		case GAME:m_GameMgr = new GameMgr(); m_GameMgr->Init(); break;
		case RESULT:m_result = new Result(); m_result->Init(); break;
		}
		switch (G_Pre_GameState){
		case DEF:break;
		case TITLE:m_title->Finish(); delete m_title; break;
		case SELECT:m_select->Finish(); delete m_select; break;
		case GAME:m_GameMgr->Finish(); delete m_GameMgr; break;
		case RESULT:m_result->Finish(); delete m_result; break;
		}
	}
	//�����łȂ��Ȃ炱����(Process)
	else{
		switch (G_MainGameState){
		case TITLE:m_title->Process(); break;
		case SELECT:m_select->Process(); break;
		case GAME:m_GameMgr->Process(); break;
		case RESULT:m_result->Process(); break;

		}
	}
	
}

void DrawMgr(){
	switch (G_MainGameState){
	case TITLE:m_title->Draw(); break;
	case SELECT:m_select->Draw(); break;
	case GAME:m_GameMgr->Draw(); break;
	case RESULT:m_result->Draw(); break;
	}
}