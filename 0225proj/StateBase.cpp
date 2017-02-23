#include "StateBase.h"

CSbase::CSbase(){

}

CSbase::~CSbase(){

}

void CSbase::Process(){

}

void CSbase::Draw(){

}

void CSbase::Init(){

}

void CSbase::Finish(){

}

void CSbase::timerinit(){
	for (int i = 0; i < TIMER_NUM; i++){
		time[i] = 0;
	}
	for (int i = 0; i < PHADE_TIMER_NUM; i++){
		phade_time[i] = 0;
	}

}
//状態に内蔵されたタイマー()オブジェクトにも内蔵
int CSbase::timer(int i){
	
	time[0] += 1;
	if (time[0] >= i){
		time[0] = 0;
		return 1;
	}
	else{
		return 0;
	}
}
//上を２つ以上使用するときの２引数版
int CSbase::timer(int i, int n){
	time[n] += 1;
	if (time[n] >= i){
		time[n] = 0;
		return 1;
	}
	else{
		return 0;
	}
}
//フェードアウトように別枠のタイマー
int CSbase::phade_timer(int i){
	phade_time[0] += 1;
	if (phade_time[0] >= i){
		phade_time[0] = 0;
		return 1;
	}
	else{
		return 0;
	}
}
//上を２つ以上使用するときの２引数版
int CSbase::phade_timer(int i, int n){
	phade_time[n] += 1;
	if (phade_time[n] >= i){
		phade_time[n] = 0;
		return 1;
	}
	else{
		return 0;
	}
}