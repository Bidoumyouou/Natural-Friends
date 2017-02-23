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
	
	E_PHADEMODE PHADEMODE;//���Ԃ̃t�F�[�h�A�E�g��
	int mode;//�����̃t�F�[�h�̎��s���ǂ̏�Ԃ�
	int alpha;//�A���t�@�u�����h�l(�ꕔ�̃t�F�[�h�ŗ��p)
	bool endflag;//�I�������true�ɂȂ�t�F�[�h�N���X���j�������
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