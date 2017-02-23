#ifndef DEF_TITLE_H
#define DEF_TITLE_H
#include"StateBase.h"
#include"Resource.h"
#include "state.h"

class Title: public CSbase{
private:
	int cursol = 0;
	int pushflag = 0;
public:
	Title();
	~Title();
	void Init();
	void Finish();
	void Process();
	void Draw();
};

extern Title* m_title;
#endif