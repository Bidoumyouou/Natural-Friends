#include "DxLib.h"
#include "Resource.h"

////�摜

////////�^�C�g��
int G_IMAGE_TITLE[3];
////////�Q�[��
int G_IMAGE_ENEMY[4];
////////���U���g

C_Graph P_Graph[2];//�v���C���[
C_Graph Back_Graph[4];//�w�i
C_Graph Timer_Graph;//�^�C���w�i
C_Graph HpFrame_Graph;//HP�o�[�̃t���[��
C_Graph HpBar_Graph;//HP�o�[�{��
C_Font OldEng_Font;

//�T�E���h
int G_MUSIC_00;//0~�̓^�C�g��

void ResouceLoad() {
	//�v���C���[�摜�̃��[�h
	//P_Graph[0].Load("picture/testplayer.png", 1, 3, 3, 1, 90, 90);
	P_Graph[0].Load("picture/��.png", 0);
	P_Graph[1].Load("picture/testplayer.png", 1, 3, 3, 1, 90, 90);
	//�w�i�摜�̃��[�h
	Back_Graph[0].Load("picture/city.png", 0);
	G_IMAGE_TITLE[0] = LoadGraph("picture/title/�X�[�p�[�o�Z��`.png");
	G_IMAGE_TITLE[1] = LoadGraph("picture/title/�X�[�p�[�o�Z��`2.png");

	//UI�֌W�摜�̃��[�h
	Timer_Graph.Load("picture/ui/time_bg.png");
	HpFrame_Graph.Load("picture/ui/hp_frame.png");
	HpBar_Graph.Load("picture/ui/hp_bar.png");

	//�t�H���g�̃��[�h
	OldEng_Font.Load("Old English Text MT", "font/OLDENGL.TTF", 45);



	int a = LoadDivGraph("picture/MainGames/spill.png", 4, 2, 2, 32, 32, G_IMAGE_ENEMY);

	
	G_MUSIC_00 = LoadSoundMem("sound/music/�s���A�q���[���[�Y.mp3");//�X�e�[�W�I��
}

//mode=0��loadgraoh mode=1��loaddivgraph
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
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		return;
	}
	Handle = CreateFontToHandle(fontname, fontsize, thick, fonttype);
}
