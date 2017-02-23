//#include"DxLib.h"
#include"CommonClass.h"
void MyDrawRotaGraph(Vector2 v, int GrHandle, int TransFlag , int TurnFlag , double ExRate , double Angle ) {
	DrawRotaGraph(v.x, v.y, ExRate, Angle, GrHandle, TransFlag, TurnFlag);
}
bool practiceflag = 0;

unsigned int White = GetColor(255,255,255);

void DebugString(Vector2 _v, char* _string){
	DrawFormatString(_v.x, _v.y, White, _string);

}
