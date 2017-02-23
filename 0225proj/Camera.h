#pragma once
#include "CommonClass.h"

//‰¼’u‚«
#define CAMERARANGE 640

class C_Camera {
public:

	Vector2 pos;
	Vector2 UpperLeft_pos;
	Vector2 size;

	Vector2 player_pos[2];
	void init();
	void Process();
	void Draw();
};

extern C_Camera Camera;