//�L�[�ƃ}�E�X�̓��͂�ϐ��Ɋi�[����
#include"Dxlib.h"
#include"key.h"
#include"phadeout.h"

C_Key sKey[256];
C_Mouse sMouse[2];//�E�N���b�N�ƍ��N���b�N
C_Joypad Pad[2];//1P��2P
int Key[256];
int Mouse[3];
int MouseX, MouseY;

int C_Key::gpUpdateKey() {
	char tmpKey[KEY_N]; //���݂̃L�[�̓��͏�Ԃ��i�[����
	C_Key *p;

	GetHitKeyStateAll(tmpKey); //�S�ẴL�[���͏�Ԃ𓾂�
	if (phade->getmode() != DEF_PHADE) { return 0; } 		//�t�F�[�h�A�E�g�̓r���łȂ����
		
	
	for (int i = 0; i < KEY_N; i++) {
		p = &sKey[i];
		if (tmpKey[i] != 0) {//i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			p->var == 0 ? p->down = true : p->down = false;
			p->var++;//���Z

		}
		else {
			p->var != 0 ? p->up = true : p->up = false;
			p->var = 0;
		}
		//push�̔���
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
	char tmpMouse[MOUSE_N]; //���݂̃L�[�̓��͏�Ԃ��i�[����
	GetMousePoint(&C_Mouse::pos.x, &C_Mouse::pos.y);
	//GetHitKeyStateAll(tmpKey); //�S�ẴL�[���͏�Ԃ𓾂�
	if (phade->getmode() == DEF_PHADE) {		//�t�F�[�h�A�E�g�̓r���łȂ����

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
	//�L�[�R���t�B�O�����̍ۂ͂��̎d�l���������ꂽ��
	if(_n == 0) {
		//�L�[�ƃp�b�h
		if (PAD_MODE != 0) {
			//�W���C�p�b�g�̃A�i���O�ȃ��o�[���
			GetJoypadAnalogInput(&xbuf, &ybuf, DX_INPUT_PAD1);

			var = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		}
		else {
			var = GetJoypadInputState(DX_INPUT_KEY);
		}
	}
	if (_n == 1) {
		//�p�b�h���̂Q
		if (PAD_MODE != 0) {
			var = GetJoypadInputState(DX_INPUT_PAD2);
			//�W���C�p�b�g�̃A�i���O�ȃ��o�[���
			GetJoypadAnalogInput(&xbuf, &ybuf, DX_INPUT_PAD2);

		}
		else {
			var = GetJoypadInputState(DX_INPUT_PAD1);
			//�W���C�p�b�g�̃A�i���O�ȃ��o�[���
			GetJoypadAnalogInput(&xbuf, &ybuf, DX_INPUT_PAD1);

		}
	}
	//�e���͍��ڂ̉����ꂽ�t���[�����i�[
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
	
	//�W���C�p�b�h���P���O�Ȃ�1P�̂݁A�Q�Ȃ�1P��2P
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
