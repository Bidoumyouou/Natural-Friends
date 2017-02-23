#pragma once

#include "DxLib.h"

//アニメ関数（ループ）
//引数は(x座標, y座標, 画像枚数, 画像配列のポインタ, 1コマのフレーム数, 現在のコマを記憶するint型ポインタ（基本0で初期化）, アニメON/OFF)
int AnimeLoop(int x, int y, int komasuu, int *handle, int oneframe, int *framemo , bool flag = TRUE);

int AnimeLoop2(int komasuu, int * handle, int oneframe, int * framemo, bool flag);

int AnimeFrame2(int komasuu, int * handle, int * oneframes, int * framemo, bool flag);

//アニメ関数（各コマフレーム数指定）
//引数は(x座標, y座標, 画像枚数, 画像配列のポインタ, 各コマを表示するフレーム数の配列, 現在のコマを記憶するint型ポインタ（基本0で初期化）, アニメON/OFF)
int AnimeFrame(int x, int y, int komasuu, int *handle, int *oneframes, int *framemo, bool flag = TRUE);

 
//戻り値は各関数共通して、アニメの最終フレームのみTRUEになります