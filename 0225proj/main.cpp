#include "DxLib.h"
#include "key.h"
#include "main.h"
#include "state.h"
#include "Resource.h"
#include "phadeout.h"
#include "CommonClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	SetMainWindowText("Proj0225");			//ウィンドウタイトルをセット
	ChangeWindowMode(TRUE);					//ウィンドウモードに変更
											//ウィンドウサイズの変更
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();								//DXライブラリ初期化
	SetDrawScreen(DX_SCREEN_BACK);			//描画先を裏画面に設定
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(TRUE);		//ウィンドウサイズを自由に変更できる
	ResouceLoad();
	G_MainGameState = DEF;
	G_Pre_GameState = DEF;
	G_Next_GameState = TITLE;
	//m_title = new Title();
	//m_GameMgr = new GameMgr();
	//m_result = new Result();
	int joynum = GetJoypadNum();
	

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !clsDx() && !C_Joypad::gpUpdatePadAll() &&  !C_Key::gpUpdateKey() && !C_Mouse::gpUpdateMouse()){
		//仮処理
		stateMgr();
		phadeMgr();
		
	}
	
	return 0;
}