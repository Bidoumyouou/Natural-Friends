#ifndef DEF_SELECT_H
#define DEF_SELECT_H
#include"StateBase.h"

class Select:public CSbase{
private:

public:
	Select();
	~Select();
	void Init();
	void Finish();
	void Process();
	void Draw();
};

extern Select* m_select;
#endif