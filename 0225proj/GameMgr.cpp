#include "GameMgr.h"
#include "Dxlib.h"
#include "key.h"

#include "class.h"
#include "Player.h"
//以下はテスト以外では不要
#include"ObjectList.h"
#include"Camera.h"
#include"View.h"
#include"HitBox.h"

#include"Effect.h"
//////////////////////
//GameMgrクラス
//旧来のクラスを使わないプログラムでいうところの
//「ゲームのメインモードのWhileループ内」に相当する。
//ゲームオーバーになったときなどは
//G_Next_GameState = RESULT などと書くと
//リザルトに移行できる。
//
//
///////////////////////
GameMgr::GameMgr(){
	timerinit();
	Camera.init();
	View.init();
	View.mgr = this;//Viewクラスに
	stagesize = View.Back_G.size.x;//フィールドのサイズ（現在は画像サイズに依存）
	t = 0;
	time = 99;
	PlaySoundMem(Battle_Sound.Handle, DX_PLAYTYPE_LOOP);
}

GameMgr::~GameMgr(){
	

}

void GameMgr::Process(){
	Camera.Process();
	View.Process();

	//時間経過を測る
	t++;
	if (t >= START_FRAME && t % 60 == 0) time--;
	if (time < 0) time = 0;

	Object_Process();
	//Tが押されたらクラス一発作成
	if (sKey[KEY_INPUT_T].var == 1){
		C_Player::Make();
	}

}

void GameMgr::Object_Process()
{
	
	C_Player::AllProcess();
	C_HitBox::AllProcess();
	C_Effect::AllProcess();
	//deleteflagをtrueにしたHitBoxを削除する
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
	//テスト用のオブジェクトの設置
	player[0] = new C_Player(0);
	player[1] = new C_Player(1);

	//ステータス変更点(炎)
	Status[HONO].slash_A = HONO_SLASH_A;

	//ステータス変更点(水)

	//ステータス変更点(木)


}
void GameMgr::Finish(){
	//モード遷移時に削除したいオブジェクトを
	//削除したり初期化したりする
	C_Player::AllDelete();
	C_HitBox::AllDelete();

	StopSoundMem(Battle_Sound.Handle);
}

GameMgr* m_GameMgr;