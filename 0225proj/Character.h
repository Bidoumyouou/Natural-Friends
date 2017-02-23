#pragma once

//��b�X�e
#define SLASH_HEIGHT 40
#define SLASH_SPEED 10
#define SLASH_CHARGE_TIME 15
#define SLASH_RANGE_UNIT 100 //�`���[�W���x��1���̐L�т̒���
#define SHOT_RANGE 450
#define SHOT_HEIGHT 300
#define SHOT_WIDE 130
#define SHOT_SPEED 10
#define SHOT_WAIT 20 //�������U�����o��܂ł̎���
#define SHOT_TIME 60 //�������U�����o�Ă��鎞��
#define COUNTER_TIME 20 //�J�E���^�[�̏o�Ă��鎞��
#define COUNTER_WAIT 40 //�J�E���^�[��̍d��
#define SLASH_A 300
#define SLASH_BACK 50
#define SHOT_A 700
#define SHOT_BACK 70
#define COUNTER_A 600
#define COUNTER_BACK 100

//�L�������̕ύX�_
#define HONO_SLASH_A 0

enum CHARACTER {
	HONO,
	MIZU,
	KI,
	CHARACTER_N
};

typedef struct{
public:
	int slash_speed = SLASH_SPEED;
	int slash_chrge_time = SLASH_CHARGE_TIME;
	int slash_lange_unit = SLASH_RANGE_UNIT;
	int shot_range = SHOT_RANGE;
	int shot_speed = SHOT_SPEED;
	int shot_wait = SHOT_WAIT;
	int shot_time = SHOT_TIME;
	int counter_time = COUNTER_TIME;
	int counter_wait = COUNTER_WAIT;
	//�U���X�e
	int slash_A = SLASH_A;
	int slash_Back = SLASH_BACK;
	int shot_A = SHOT_A;
	int shot_Back = SHOT_BACK;
	int counter_A = COUNTER_A;
	int counter_Back = COUNTER_BACK;
}S_Status;

//extern S_Status Status[CHARACTER_N];