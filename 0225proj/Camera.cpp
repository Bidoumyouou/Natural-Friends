#include "Camera.h"
#include "Player.h"
#include"stdlib.h"

void C_Camera::init()
{
	size.Set(WINDOW_X,WINDOW_Y);

}

void C_Camera::Process()
{
	//プレイヤー同士の座標の中央位置を指定
	player_pos[0] = player[0]->pos;
	player_pos[1] = player[1]->pos;
	pos.x =(player_pos[0].x + player_pos[1].x) / 2;
	if (pos.x < (0 + (WINDOW_X / 2)))
		pos.x = 0 + ((WINDOW_X / 2));
	else if (pos.x >(BACKWIDTH - (WINDOW_X / 2)))
		pos.x = BACKWIDTH - (WINDOW_X / 2);
	pos.y = WINDOW_Y / 2;
	Vector2 harfsize; harfsize.Set(size.x / 2, size.y / 2);
	UpperLeft_pos = pos - harfsize;
}

void C_Camera::Draw()
{
	//カメラになりうる場所に四角形で
	//DrawBox(UpperLight_pos.x, UpperLight_pos.y, UpperLight_pos.x + size.x, UpperLight_pos.y + size.y, RED, 0);
}

C_Camera Camera;