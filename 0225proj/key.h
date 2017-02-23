#ifndef DEF_KEY_H
#define DEF_KEY_H
#include"CommonClass.h"

int gpUpdateKey();
int gpUpdateMouse();


class C_Key {
public:
	//メンバ定数(書き換え不能)
	static const int KEY_N = 256;

	int var = 0;
	bool up = false;
	bool down = false;
	bool push = false;//押され続けてる間
	static int gpUpdateKey();
	
	
};

class C_Mouse {
public:
	static const int MOUSE_N = 3;

	int var = 0;
	static Vector2 pos;//現在のマウスの座標
	Vector2 start_pos;//クリックしたときの座標
	Vector2 end_pos;//離したときの座標

	bool up = false;
	bool down = false;
	static int gpUpdateMouse();

};
#define PAD_MODE 0//0.. 1Pがキー 2Pがパッド 1..1Pがパッドorキー 2Pがパッド
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
	int var = 0;	//全てのパッド入力情報がマスク形式で入っている
	int Button[10];
	int Down;
	int Up;
	int Left;
	int Right;
	int xbuf, ybuf;//ジョイパッド十字のアナログの入力値を得る
	//双方 -1000~1000の値を取る
	void gpUpdatePad(int _n);
	static int gpUpdatePadAll();
};

extern int Key[256];
extern C_Joypad Pad[2];
extern C_Key sKey[256];
extern C_Mouse sMouse[2];
#endif