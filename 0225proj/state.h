#ifndef DEF_STATE_H
#define DEF_STATE_H

void stateMgr();

enum E_MAINGAMESTATE{
	DEF,
	TITLE,
	E_MGSTATE_STAGEINIT,
	E_MGSTATE_GAMESTART,//ゲーム開始エフェクト
	GAME,
	E_MGSTATE_GAMEEND,//ゲーム終了時エフェクト
	RESULT,//スコア表示(クリア画像表示、コンティニューチェック表示)
	E_MGSTATE_END,//ゲームの終了処理
	SELECT,
};

extern E_MAINGAMESTATE G_MainGameState;
extern E_MAINGAMESTATE G_Pre_GameState;
extern E_MAINGAMESTATE G_Next_GameState;
#endif