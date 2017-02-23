#ifndef DEF_RESULT_H
#define DEF_RESULT_H
#include"StateBase.h"

class Result:public CSbase{
private:

public:
	Result();
	~Result();
	void Init();
	void Finish();
	void Process();
	void Draw();
};

extern Result* m_result;
#endif