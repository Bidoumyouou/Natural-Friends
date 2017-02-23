#include "Dammy.h"
#include"ObjectList.h"
#include <DxLib.h>
#include "GV.h"

//////////////////////
//派生クラスDammy
//・プロジェクトに追加したのち
//GameMgr.cppにインクルードすれば動く(はず)
//includeファイルの循環参照で困ったら
//ヘッダファイルでクラスの前方宣言を
//includeの代わりに用いるべし
//・コピーした後はGameMgr::ObjectProcessに<クラス名>::AllProcess()を
//書き入れる(Drawも同様、ついでに必要ならAllDelete()も)
///////////////////////

//基底クラスのint引数付きのものと同じタイミングで呼ぶために
//不要に見えるイニシャライザを持つ
Dammy::Dammy(int arynum) : ObjectBase(arynum) {
	exi[arraynum] = true;
	object_n++;
	id = total;
	total++;
	///////////////
}



Dammy::~Dammy(){
	///////////////
	exi[arraynum] = false;
	object_n--;
}

void Dammy::Process(){
	ObjectBase::Process();
}

void Dammy::Draw(){
	ObjectBase::Process();
	//仮置きの正方形描画
	DrawBox(x, y, x + 100, y + 100, GetColor(255, 255, 255), 1);
	DrawFormatString(x, y, BLUE, "ID = %d", id);
}

//クラスのProcessを一括で動かす静的メンバ関数
void Dammy::AllProcess(){
	for (int i = 0; i < total; i++){
		if (Dammy::exi[i]){
			if (Dammy::exi[i] == true)
			dammy[i]->Process();
		}
	}
}

//クラスのDrawを一括で動かす静的メンバ関数
void Dammy::AllDraw(){
	for (int i = 0; i < total; i++){
		if (Dammy::exi[i]){
			if(Dammy::exi[i] == true)
			dammy[i]->Draw();
		}
	}
}

//インスタンスの作成
void Dammy::Make(){
	for (int i = 0; i < object_n + 1; i++){
		if (Dammy::exi[i] == 0){
			dammy[i] = new Dammy(i);
			return;
		}
	}
}

//インスタンスの削除
void Dammy::Delete(int i){
	if (Dammy::object_n > 0){
		delete dammy[i];
	}
}

//インスタンスの全削除
void Dammy::AllDelete() {
	for (int i = 0; i < DAMMY_MAX;i++) {
		if (Dammy::exi[i] == true) {
			delete dammy[i];
		}
	}
}
int Dammy::GetObject_n(){
	return object_n;
}

int Dammy::total = 0;
int Dammy::object_n = 0;//静的メンバ変数の実体
bool Dammy::exi[DAMMY_MAX] = {};
Dammy* dammy[DAMMY_MAX];

//////////////////////////////
//クラス未習得者向けCips
//・クラスは構造体を拡張したもので
//変数のほかに関数をいくつか持てる(メンバ変数、メンバ関数)
//(ProcessやDrawなどは実際にそうなっている)
//・クラスのメンバ関数内では内部のメンバ変数、関数を特に意識せず使える
//ex: メンバ変数に HP が入っているなら HP = 114514 
//・クラス外部から利用するときは ->(アロー) でオブジェクトを指定する
//ex 外部からdammyオブジェクトのHPを参照するときは
//dammy->HP = 0;
//HitCheck()関数を呼ぶなら
//dammy->HitCheck()
//(追加で)
//・staticで宣言されてるメンバを参照するときは
//Dammyクラスが　static TotalAttack　のばあい
//Dammy::TotalAttack = 60
//となる
//
///////////////////////////////