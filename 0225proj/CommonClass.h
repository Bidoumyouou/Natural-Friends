#pragma once
#include"DxLib.h"

#include<math.h>
#include "GV.h"
extern bool practiceflag;

//x,yのメンバを持つ汎用クラス
class Vector2 {
public:
	int x;
	int y;
	//値の設定

	void Set(const int _x,const int _y) {
		x = _x;
		y = _y;
	}
	//値の設定
	void Set(const Vector2 _V) {
		*this = _V;
	}
	//距離
	double distance(Vector2 _V) {
		double temp = sqrt((_V.x - x) * (_V.x - x) + (_V.y - y) * (_V.y - y));
		return temp;
	}
	//距離
	double distance(const int _x, const int _y) {
		double temp = sqrt((_x - x) * (_x - x) + (_y - y) * (_y - y));
		return temp;
	}
	//四角形とのあたり判定
	bool InSquare (                           const int _x1, const int _y1, const int _x2, const int _y2) {
		if (!(x >= _x1 && x < _x2))return false;
		if (!(y >= _y1 && y < _y2))return false;
		return true;
	}
	bool InSquare (const Vector2 _V1, Vector2 _V2                                   ) {return InSquare(_V1.x, _V1.y, _V2.x, _V2.y);}
	bool InSquare2(const Vector2 _V,				                  int _x, int _y) {return InSquare(_V.x, _V.y, _V.x + _x, _V.y + _y);}
	bool InSquare2(                           const int _x, int _y, int _x2, int _y2) {return InSquare(_x, _y, _x + _x2, _y + _y2);}

	//演算
	//+
	Vector2 operator+(const Vector2 _V) {
		Vector2 ans;
		ans.x = this->x + _V.x;
		ans.y = this->y + _V.y;
		return ans;
	}
	//-
	Vector2 operator-(const Vector2 _V) {
		Vector2 ans;
		ans.x = x - _V.x;
		ans.y = y - _V.y;
		return ans;
	}

	
	
};

//四角形クラス
class Square{
public:
	Vector2 v[4];//必ずv[0]..top v[1]...bottom v[2]...right v[3]...leftにすること
	//四角形の中に引数の頂点があるか
	bool inSquare(Vector2 _v) {
		if (!(_v.y < v[1].y && _v.y > v[0].y)) { 
			return false; 
		}
		if (!(_v.x >= v[3].x && _v.x <= v[2].x)) { 
			return false; 
		}
		return true;
	}
	//セット
	void Set(Vector2 _v0, Vector2 _v1, Vector2 _v2, Vector2 _v3) {
		v[0] = _v0; v[1] = _v1; v[2] = _v2; v[3] = _v3;
	}
	void Set(int _x0, int _y0, int _x1, int _y1, int _x2, int _y2, int _x3, int _y3) {
		v[0].Set(_x0, _y0); v[0].Set(_x1, _y1); v[0].Set(_x2, _y2); v[0].Set(_x3, _y3);
	}
	//2頂点セット
	void Set2p(Vector2 _v0, Vector2 _v1) {
		v[0].y = v[2].y = _v0.y;
		v[0].x = v[3].x = _v0.x;
		v[1].y = v[3].y = _v1.y;
		v[1].x = v[2].x = _v1.x;
	}
	void Set2p(int _x0, int _y0, int _x1, int _y1) {
		Vector2 tmp[2];
		tmp[0].x = _x0; tmp[0].y = _y0;
		tmp[1].x = _x1; tmp[1].y = _y1;
		Set2p(tmp[0], tmp[1]);
	}
	int Length2p() {
		return (v[0].x - v[1].x);
	}
};

// 0 > 1 > 2 > 1 >0 > 1...みたいに遷移する値を有するクラス 
class Loop_int {
public:
	int var = 0;
	bool up = true;//trueならupfalseならdown(default = true)
	void rapup(int _min, int _max) {
		if (up == true) {
			if (var == _max) {
				up = false;
			}
			add(up);
		}
		else {
			if (var == _min) {
				up = true;
			}
			add(up);
		}
	}
private: 
	void add(bool _up) {
		if (_up == true) {var++;}else {var--;}
	}
};
class Up_int {
public:
	int var = 0;
	void Up(int _min, int _max, int _degree = 1) {
		if (var >= _max) {
			var = _min;
		}
		else {
			var += _degree;
		}
	}
};
// 0 > 1 > 2 > 0 > 1...みたいに遷移する関数 
//int rapup2(int _n,int _max,int _min) {
//	if (_n == _max ) {
//		return _min;
//	}
//	else {
//		return _n++;
//	}
//}


extern unsigned int White;
#define WHITE 65535;

void MyDrawRotaGraph(Vector2 v, int GrHandle, int TransFlag = 1, int TurnFlag = FALSE, double ExRate = 1.0, double Angle = 0.0);
void DebugString(Vector2 _v, char* _string);