#ifndef DEF_KEY_H
#define DEF_KEY_H
#include"CommonClass.h"

int gpUpdateKey();
int gpUpdateMouse();


class C_Key {
public:
	//�����o�萔(���������s�\)
	static const int KEY_N = 256;

	int var = 0;
	bool up = false;
	bool down = false;
	bool push = false;//�����ꑱ���Ă��
	static int gpUpdateKey();
	
	
};

class C_Mouse {
public:
	static const int MOUSE_N = 3;

	int var = 0;
	static Vector2 pos;//���݂̃}�E�X�̍��W
	Vector2 start_pos;//�N���b�N�����Ƃ��̍��W
	Vector2 end_pos;//�������Ƃ��̍��W

	bool up = false;
	bool down = false;
	static int gpUpdateMouse();

};
#define PAD_MODE 0//0.. 1P���L�[ 2P���p�b�h 1..1P���p�b�hor�L�[ 2P���p�b�h
#define PAD_Z 0
#define PAD_X 1
#define PAD_C 2
#define PAD_A 3
#define PAD_S 4
#define PAD_D 5
#define PAD_Q 6
#define PAD_W 7
#define PAD_ESC 8
#define PAD_SPACE 9
class C_Joypad {
public:
	int var = 0;	//�S�Ẵp�b�h���͏�񂪃}�X�N�`���œ����Ă���
	int Button[10];
	int Down;
	int Up;
	int Left;
	int Right;
	int xbuf, ybuf;//�W���C�p�b�h�\���̃A�i���O�̓��͒l�𓾂�
	//�o�� -1000~1000�̒l�����
	void gpUpdatePad(int _n);
	static int gpUpdatePadAll();
};

extern int Key[256];
extern C_Joypad Pad[2];
extern C_Key sKey[256];
extern C_Mouse sMouse[2];
#endif