#include "ObjectBase.h"
#include "DxLib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
ObjectBase* Object[OBJECT_MAX];
//コンストラクタ
ObjectBase::ObjectBase(int arynum) 
{
	
	t = 0;
	state_t = 0;
	//x = 100 + GetRand(400);
	//y = 100 + GetRand(400);
	arraynum = arynum;
	
	
	Object[arraynum]->global_object_n++;
	global_id = global_total;
	global_total++;
	
}
ObjectBase::ObjectBase(){}
ObjectBase::~ObjectBase(){
	global_object_n--;
	
}
void ObjectBase::Process(){	
	//時間変化
	t++;
	
	//左上座標のセット
	SetUpperLeft();
	
}

void ObjectBase::Draw(){}

void ObjectBase::Init(){}

void ObjectBase::Exit(){}

void ObjectBase::AllProcess(){}

void ObjectBase::AllDraw(){}

void ObjectBase::Make(){}

void ObjectBase::Delete(int i){

}

void ObjectBase::SetUpperLeft()
{
	UpperLeft_pos.x = pos.x - (Graph.size.x / 2);
	UpperLeft_pos.y = pos.y - (Graph.size.y / 2);
	LowerRight_pos.x = UpperLeft_pos.x + Graph.size.x;
	LowerRight_pos.y = UpperLeft_pos.y + Graph.size.y;
}

bool ObjectBase::CompState() {
	//if (Pre_State != Main_State)
	//	return true;
	//else
	return false;
}



int ObjectBase::global_object_n = 0;//静的メンバ変数の実体
int ObjectBase::global_total = 0;



