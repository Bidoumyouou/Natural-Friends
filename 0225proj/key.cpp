//キーとマウスの入力を変数に格納する
#include"Dxlib.h"
#include"key.h"
#include"phadeout.h"

C_Key sKey[256];
C_Mouse sMouse[2];//右クリックと左クリック
C_Joypad Pad[2];//1Pと2P
int Key[256];
int Mouse[3];
int MouseX, MouseY;

int C_Key::gpUpdateKey() {
	char tmpKey[KEY_N]; //現在のキーの入力状態を格納する
	C_Key *p;

	GetHitKeyStateAll(tmpKey); //全てのキー入力状態を得る
	if (phade->getmode() != DEF_PHADE) { return 0; } 		//フェードアウトの途中でなければ
		
	
	for (int i = 0; i < KEY_N; i++) {
		p = &sKey[i];
		if (tmpKey[i] != 0) {//i番のキーコードに対応するキーが押されていたら
			p->var == 0 ? p->down = true : p->down = false;
			p->var++;//加算

		}
		else {
			p->var != 0 ? p->up = true : p->up = false;
			p->var = 0;
		}
		//pushの判定
		p->var != 0 ? p->push = true : p->push = false;
	}
	return 0;
}

	int gpUpdateKey() {
	

	return 0;
}

int gpUpdateMouse() {
	
	return 0;
}

int C_Mouse::gpUpdateMouse() {
	char tmpMouse[MOUSE_N]; //現在のキーの入力状態を格納する
	GetMousePoint(&C_Mouse::pos.x, &C_Mouse::pos.y);
	//GetHitKeyStateAll(tmpKey); //全てのキー入力状態を得る
	if (phade->getmode() == DEF_PHADE) {		//フェードアウトの途中でなければ

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			sMouse[0].var == 0 ? sMouse[0].down = true : sMouse[0].down = false;
			if (sMouse[0].down) { sMouse[0].start_pos = C_Mouse::pos; }
			sMouse[0].var++;
		}
		else {
			sMouse[0].var != 0 ? sMouse[0].up = true : sMouse[0].up = false;
			if (sMouse[0].up) { sMouse[0].end_pos = C_Mouse::pos; }
			sMouse[0].var = 0;

		}
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
			sMouse[1].var == 0 ? sMouse[1].down = true : sMouse[1].down = false;
			if (sMouse[1].down) { sMouse[1].start_pos = C_Mouse::pos; }
			sMouse[1].var++;
		}
		else {
			sMouse[1].var != 0 ? sMouse[1].up = true : sMouse[1].up = false;
			if (sMouse[1].up) { sMouse[1].end_pos = C_Mouse::pos; }
			sMouse[1].var = 0;

		}
	}
	return 0;
}
Vector2 C_Mouse::pos;

void C_Joypad::gpUpdatePad(int _n)
{
	//キーコンフィグ実装の際はこの仕様を見直されたし
	if(_n == 0) {
		//キーとパッド
		if (PAD_MODE != 0) {
			//ジョイパットのアナログなレバー情報
			GetJoypadAnalogInput(&xbuf, &ybuf, DX_INPUT_PAD1);

			var = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		}
		else {
			var = GetJoypadInputState(DX_INPUT_KEY);
		}
	}
	if (_n == 1) {
		//パッドその２
		if (PAD_MODE != 0) {
			var = GetJoypadInputState(DX_INPUT_PAD2);
			//ジョイパットのアナログなレバー情報
			GetJoypadAnalogInput(&xbuf, &ybuf, DX_INPUT_PAD2);

		}
		else {
			var = GetJoypadInputState(DX_INPUT_PAD1);
			//ジョイパットのアナログなレバー情報
			GetJoypadAnalogInput(&xbuf, &ybuf, DX_INPUT_PAD1);

		}
	}
	//各入力項目の押されたフレームを格納
	var & PAD_INPUT_DOWN  ?  Down++ :  Down = 0;
	var & PAD_INPUT_UP    ?   Up++  :    Up = 0;
	var & PAD_INPUT_RIGHT ?  Right++: Right = 0;
	var & PAD_INPUT_LEFT  ?  Left++ :  Left = 0;
	/*if (var & PAD_INPUT_1 == 0) {
		Button[PAD_Z] = 0;
	}
	else {
		Button[PAD_Z]++;
	}*/
	var & PAD_INPUT_1 ? Button[PAD_Z]++ : Button[PAD_Z] = 0;
	var & PAD_INPUT_2 ? Button[PAD_X]++ : Button[PAD_X] = 0;
	var & PAD_INPUT_3 ? Button[PAD_C]++ : Button[PAD_C] = 0;
	var & PAD_INPUT_4 ? Button[PAD_A]++ : Button[PAD_A] = 0;
	var & PAD_INPUT_5 ? Button[PAD_S]++ : Button[PAD_S] = 0;
	var & PAD_INPUT_6 ? Button[PAD_D]++ : Button[PAD_D] = 0;
	var & PAD_INPUT_7 ? Button[PAD_Q]++ : Button[PAD_Q] = 0;
	var & PAD_INPUT_8 ? Button[PAD_W]++ : Button[PAD_W] = 0;
	var & PAD_INPUT_9 ? Button[PAD_ESC]++ : Button[PAD_ESC] = 0;
	var & PAD_INPUT_10 ? Button[PAD_SPACE]++ : Button[PAD_SPACE] = 0;
	

}
 
int C_Joypad::gpUpdatePadAll()
{
	
	//ジョイパッドが１個か０個なら1Pのみ、２個なら1Pと2P
	if (PAD_MODE != 0) {
		if (GetJoypadNum() >= 2) {
			Pad[0].gpUpdatePad(0);
			Pad[1].gpUpdatePad(1);
		}
		else {
			Pad[0].gpUpdatePad(0);
		}
	}
	else {
		Pad[0].gpUpdatePad(0);
		Pad[1].gpUpdatePad(1);
	}
	return 0;
}
