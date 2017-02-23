#ifndef DEF_PHADEOUT_H
#define DEF_PHADEOUT_H
extern int phadestate;



enum E_PHADEMODE{
	DEF_PHADE,
	NORMAL
};

void phadeMgr();
void phadeout(E_PHADEMODE);

class Cphade{
protected:
	
	E_PHADEMODE PHADEMODE;//何番のフェードアウトか
	int mode;//同一種のフェードの実行中どの状態か
	int alpha;//アルファブレンド値(一部のフェードで利用)
	bool endflag;//終わったらtrueになりフェードクラスが破棄される
public:
	E_PHADEMODE getmode();
	Cphade();
	Cphade(E_PHADEMODE);
	~Cphade();
	void Process();
	void Draw();

};
extern Cphade *phade;
#endif