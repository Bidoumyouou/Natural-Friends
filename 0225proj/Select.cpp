
#include "Select.h"
#include "Dxlib.h"
#include "key.h"

Select::Select(){
	timerinit();
}

Select::~Select(){

}

void Select::Init() {
	DrawGraph(0, 0, SelectBack_Graph.Handle, FALSE);
}

void Select::Process(){

}

void Select::Draw(){

}


void Select::Finish(){

}
Select* m_select;