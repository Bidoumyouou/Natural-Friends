#ifndef DEF_RESOURCE_H
#define DEF_RESOURCE_H
#include"CommonClass.h"

#define LOAD_DIV_MAX 64//�������̏��

void ResouceLoad();//�f�ޓǂݍ��݊֐�
////�摜

////////�^�C�g��
extern int G_IMAGE_TITLE[3];
////////�Q�[��
extern int G_IMAGE_ENEMY[4];
////////���U���g

//�T�E���h
extern int G_MUSIC_00;//0~�̓^�C�g��

//�摜�f�[�^�N���X

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

extern C_Graph P_Graph[2];
extern C_Graph Back_Graph[4];
extern C_Graph Timer_Graph;
extern C_Graph HpFrame_Graph;
extern C_Graph HpBar_Graph;
extern C_Font OldEng_Font;

#endif