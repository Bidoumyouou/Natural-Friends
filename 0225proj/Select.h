#ifndef DEF_SELECT_H
#define DEF_SELECT_H
#include "StateBase.h"
#include "Resource.h"
#define P_LAVA 1
#define P_MINAMO 2
#define P_SEPHI 3
#define P_RANDOM 0

typedef struct {
	int x, y;
	int C_x, C_y;
	int Handle[2];
}Cursor;

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