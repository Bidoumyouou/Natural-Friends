#include "Title.h"
#include "Dxlib.h"
#include "key.h"
#include "phadeout.h"
Title::Title(){
	cursol = 0;
	pushflag = 0;
	timerinit();
}

Title::~Title(){

}

void Title::Process(){

	if (sKey[KEY_INPUT_DOWN].var == 1){
		cursol = 1;
	}
	if (sKey[KEY_INPUT_UP].var == 1){
		cursol = 0;
	}
	if (sKey[KEY_INPUT_Z].var == 1){
		pushflag = 1;
	}
	if (pushflag > 0){
		if (pushflag == 1){
			phadeout(NORMAL);
			pushflag = 2;
		}
		if (timer(16) == 1){
			G_Next_GameState = GAME;
		}
	}
	printfDx("G_MAIN_GAMESTATE=%d",G_MainGameState);
	printfDx("time|%d", time[0]);
}

void Title::Draw(){
	DrawGraph(0, 0, G_IMAGE_TITLE[cursol], 1);

}

void Title::Init(){

}
void Title::Finish(){

}
Title* m_title;