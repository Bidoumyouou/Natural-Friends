#pragma once

#include "DxLib.h"

//�A�j���֐��i���[�v�j
//������(x���W, y���W, �摜����, �摜�z��̃|�C���^, 1�R�}�̃t���[����, ���݂̃R�}���L������int�^�|�C���^�i��{0�ŏ������j, �A�j��ON/OFF)
int AnimeLoop(int x, int y, int komasuu, int *handle, int oneframe, int *framemo , bool flag = TRUE);

int AnimeLoop2(int komasuu, int * handle, int oneframe, int * framemo, bool flag);

int AnimeFrame2(int komasuu, int * handle, int * oneframes, int * framemo, bool flag);

//�A�j���֐��i�e�R�}�t���[�����w��j
//������(x���W, y���W, �摜����, �摜�z��̃|�C���^, �e�R�}��\������t���[�����̔z��, ���݂̃R�}���L������int�^�|�C���^�i��{0�ŏ������j, �A�j��ON/OFF)
int AnimeFrame(int x, int y, int komasuu, int *handle, int *oneframes, int *framemo, bool flag = TRUE);

 
//�߂�l�͊e�֐����ʂ��āA�A�j���̍ŏI�t���[���̂�TRUE�ɂȂ�܂�