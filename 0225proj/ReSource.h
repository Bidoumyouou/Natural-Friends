#ifndef DEF_RESOURCE_H
#define DEF_RESOURCE_H
#include"CommonClass.h"

#define LOAD_DIV_MAX 64//分割数の上限

void ResouceLoad();//素材読み込み関数
////画像

////////タイトル
extern int G_IMAGE_TITLE[3];
////////ゲーム
extern int G_IMAGE_ENEMY[4];
////////リザルト

//サウンド
extern int G_MUSIC_00;//0~はタイトル

//画像データクラス

class C_Graph {
public:
	int Handle;
	int HandleArray[LOAD_DIV_MAX];
	Vector2 size;
	int Load(char *filename,int _mode = 0,int AllNum = 0, int XNum = 0, int YNum = 0, int   XSize = 0, int   YSize = 0);
private:
	
};
class C_Font {
public:
	int Handle;
	void Load(const char* fontname, const char* filename, int fontsize = -1, int thick = -1, int fonttype = -1);
};
extern C_Graph Player_Graph[3][7];
class C_Sound {
public:
	int Handle;
	void Load(const char* filename);

};


extern C_Graph P_Graph[2];
extern C_Graph Back_Graph[4];
extern C_Graph Timer_Graph;
extern C_Graph HpFrame_Graph;
extern C_Graph HpBar_Graph;
extern C_Graph Ready_Graph;
extern C_Graph Start_Graph;
extern C_Graph SelectBack_Graph;
extern C_Font OldEng_Font;
extern C_Sound Ready_Sound;
extern C_Sound Start_Sound;
extern C_Sound Select_Sound;
extern C_Sound Battle_Sound;

#endif