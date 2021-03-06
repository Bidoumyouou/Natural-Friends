#pragma once
#define OBJECT_MAX 1024 
#include"CommonClass.h"
#include"Resource.h"
//////////////////////
//基底クラスObjectBase
//・すべての派生クラスに Process Draw AllProcess 
// AllDraw Make Delete をオーバーライドするべし
//・簡単に派生クラスを作る方法はPlayer.h,Player.cppを
//プロジェクトに追加してPlayerを任意のオブジェクト名に
//置換することである。
//
//
///////////////////////

///////////////////////
//一応共通のメンバ変数として座標とt(生まれてからのフレーム数)が入っているが
//頻繁に外部から参照する要素は事前に洗い出して
//基底クラスや派生クラスに追加した上で
//共有するべし
///////////////////////

//攻撃の特性
class C_AttackStatus {
public:
	int power;//攻撃力
	int nockback;//ノックバック
	int backspeed;//ノックバックのすっぴーど
	void Set(int _power, int _nockback, int _backspeed = 8) {
		power = _power;
		nockback = _nockback;
		backspeed = _backspeed;
	}
};

enum STATE {
	DEFAULT,           //デフォルト
	SLASHCHARGE,  //通常攻撃溜め
	SLASH,        //通常攻撃
	SHOT,    //遠距離攻撃
	COUNTER,       //カウンター
	STUN,          //硬直
	DAMEGE,        //被ダメージ
	STATE_N,
};

enum E_HitMode {
	H_NONE,
	H_SLASHCHARGE,
	H_SLASH,
	H_SHOT,
	H_DEFENCE,
	H_COUNTER,
	H_HitMode_N,
};

class ObjectBase
{
public:
	//staticはクラス内でただ一つ作られる変数で表現(静的メンバ変数)
	ObjectBase();
	ObjectBase(int);
	~ObjectBase();

	virtual void Process();
	virtual void Draw();
	virtual void Init();
	virtual void Exit();
	static void AllProcess();
	static void AllDraw();
	static void Make();
	static void Delete(int);
	
	int arraynum;//このオブジェクトが実装されている実体の配列番号(IDではない)
	int global_id;//オブジェクトの通し番号
	int id;//オブジェクト種類別の通し番号(生成順)
/////////////////////////
//以上,機能させるのに必須のメンバ
/////////////////////////
	Vector2 pos;
	Vector2 draw_pos;//描画用の座標(必要なら使う)
	C_Graph Graph;//画像ハンドル等クラス
	//C_Graph G_Handle2;//画像ハンドル予備
	int z;//描画の順番
	int t;//生成されてからの時間
	int state_t;//今の状態になってからの時間
	Vector2 UpperLeft_pos;	//描画座標の左上//初期化されてないVector2変数は危険
	Vector2 LowerRight_pos; //描画座標の右下
	
	void SetUpperLeft();
	bool deleteflag;//これがtrueになると消滅する
private:
	bool CompState(); //次の状態と今の状態が違うならtrue
protected:
	bool initflag = false;
	static int global_object_n;//
	static int global_total;

};
extern ObjectBase* Object[OBJECT_MAX];

