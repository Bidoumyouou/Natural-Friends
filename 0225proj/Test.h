#ifndef DEF_TEST_H
#define DEF_TEST_H

#include "Cbase.h"

extern int Test_N;

class CCbase;

class CTest: public CCbase{
private:
public:
	CTest();
	~CTest();
	void Init();
	void Finish();
	void Process();
	void Draw();
};

extern CTest* Test;
extern void Test_Process();

#endif