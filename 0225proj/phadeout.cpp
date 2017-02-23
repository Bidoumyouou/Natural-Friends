#include"phadeout.h"
#include"Dxlib.h"
#include"GV.h"

int alpha = 0;
int phadestate = 0;
Cphade *phade = new Cphade(DEF_PHADE);



Cphade::Cphade(){
	PHADEMODE = NORMAL;
	alpha = 0;
	mode = 0;
	endflag = false;
}

Cphade::Cphade(E_PHADEMODE f){
	alpha = 0;
	mode = 0;
	endflag = false;
	PHADEMODE = f;
}

Cphade::~Cphade(){

}
void Cphade::Process(){
	switch (PHADEMODE){
	case NORMAL:
		if (mode == 0){
			alpha += 16;
		}
		if (mode == 1){
			alpha -= 16;
		}
		if (alpha > 255){
			alpha = 255;
			mode = 1;
		}
		if (alpha < 0){
			alpha = 0;
			endflag = true;
		}
		break;
	}
	//endflagがtrueになったら自己クラスを破棄する
	if (endflag == true){
		delete phade;
		phade = new Cphade(DEF_PHADE);
	}
}

void Cphade::Draw(){
	switch (PHADEMODE){
	case NORMAL:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha);
		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), 1);
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

}
E_PHADEMODE Cphade::getmode(){
	return PHADEMODE;
	
}


void phadeMgr(){
	phade->Process();
	phade->Draw();
}
//これを外部参照する
void phadeout(E_PHADEMODE f){
	if (phade->getmode() != f){
		delete phade;
		phade = new Cphade(f);
	}
}

