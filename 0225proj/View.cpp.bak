#include "View.h"
#include "Resource.h"
#include "Camera.h"
#include "Player.h"
#include "key.h"

void C_View::init()
{
	//画像ハンドルの適用
	Back_G = Back_Graph[0];
	Timer_G = Timer_Graph;
	HpFrame_G = HpFrame_Graph;
	HpBar_G = HpBar_Graph;
	OldEng_F = OldEng_Font;
}

void C_View::Draw()
{
	DrawRotaGraph((Back_G.size.x / 2) - Camera.UpperLeft_pos.x, (Back_G.size.y / 2), 1, 0, Back_G.Handle, 0);
}


int frame = 0;
int time = 99;
char Time_Char[3];

void C_View::Draw2()
{
	DrawGraph(368, 20, Timer_G.Handle, FALSE);
	DrawStringToHandle(382, 47, Time_Char, RED, OldEng_F.Handle);
	DrawGraph(20, 45, HpFrame_G.Handle, TRUE);
	DrawGraph(465, 45, HpFrame_G.Handle, TRUE);
	DrawRectGraph(25, 50, 0, 0, (int)((double)305 * ((double)player[0]->HP / MAX_HP)), 35, HpBar_G.Handle, FALSE, FALSE);
	DrawRectGraph(775 - (int)((double)305 * ((double)player[1]->HP / MAX_HP)), 50, 0, 0, (int)((double)305 *((double)player[1]->HP / MAX_HP)), 35, HpBar_G.Handle, FALSE, TRUE);
	frame++;
	if (frame % 60 == 0) time--;

	//if(sKey[KEY_INPUT_Z].var >= 1) player[0]->HP -= 10;
	//if (player[0]->HP < 0) player[0]->HP = MAX_HP;
//	player[1]->HP -= 15;
//	if (player[1]->HP < 0) player[1]->HP = MAX_HP;
}

void C_View::Process()
{
	sprintf_s(Time_Char, "%.2d", time);

}
C_View View;