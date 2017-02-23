#include "DxLib.h"
#include "Resource.h"

////画像

////////タイトル
int G_IMAGE_TITLE[3];
////////ゲーム
int G_IMAGE_ENEMY[4];
////////リザルト

C_Graph P_Graph[2];//プレイヤー
C_Graph Back_Graph[4];//背景
C_Graph Timer_Graph;//タイム背景
C_Graph HpFrame_Graph;//HPバーのフレーム
C_Graph HpBar_Graph;//HPバー本体
C_Font OldEng_Font;

//サウンド
int G_MUSIC_00;//0~はタイトル

void ResouceLoad() {
	//プレイヤー画像のロード
	//P_Graph[0].Load("picture/testplayer.png", 1, 3, 3, 1, 90, 90);
	P_Graph[0].Load("picture/炎.png", 0);
	P_Graph[1].Load("picture/testplayer.png", 1, 3, 3, 1, 90, 90);
	//背景画像のロード
	Back_Graph[0].Load("picture/city.png", 0);
	G_IMAGE_TITLE[0] = LoadGraph("picture/title/スーパー双六列伝.png");
	G_IMAGE_TITLE[1] = LoadGraph("picture/title/スーパー双六列伝2.png");

	//UI関係画像のロード
	Timer_Graph.Load("picture/ui/time_bg.png");
	HpFrame_Graph.Load("picture/ui/hp_frame.png");
	HpBar_Graph.Load("picture/ui/hp_bar.png");

	//フォントのロード
	OldEng_Font.Load("Old English Text MT", "font/OLDENGL.TTF", 45);



	int a = LoadDivGraph("picture/MainGames/spill.png", 4, 2, 2, 32, 32, G_IMAGE_ENEMY);

	
	G_MUSIC_00 = LoadSoundMem("sound/music/ピュアヒューリーズ.mp3");//ステージ選択
}

//mode=0でloadgraoh mode=1でloaddivgraph
int C_Graph::Load(char *filename, int _mode, int AllNum, int XNum, int YNum, int   XSize, int   YSize) {
	switch (_mode) {
	case 0:Handle = LoadGraph(filename); 	GetGraphSize(Handle, &size.x, &size.y); break;
	case 1:LoadDivGraph(filename, AllNum, XNum, YNum, XSize, YSize, HandleArray);	GetGraphSize(HandleArray[0], &size.x, &size.y); break;

	}
	return 0;
}

void C_Font::Load(const char * fontname, const char * filename, int fontsize, int thick, int fonttype){
	int filesize = FileRead_size(filename);
	int filehandle = FileRead_open(filename);
	void *buffer = malloc(filesize);
	FileRead_read(buffer, filesize, filehandle);
	DWORD font_num = 0;
	if (AddFontMemResourceEx(buffer, filesize, NULL, &font_num) != 0) {}
	else {
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		return;
	}
	Handle = CreateFontToHandle(fontname, fontsize, thick, fonttype);
}
