#ifndef DEF_CBASE_H
#define DEF_CBASE_H
#include "DXlib.h"
#define TIMER_NUM 256
#define PHADE_TIMER_NUM 16
class CSbase{
protected:
	void timerinit();
public:
	CSbase();
	~CSbase();
	virtual void Init();
	virtual void Finish();
	virtual void Process();
	virtual void Draw();
	int timer(int);
	int timer(int, int);
	int time[TIMER_NUM];
	int phade_timer(int);
	int phade_timer(int, int);
	int phade_time[PHADE_TIMER_NUM];

};

#endif