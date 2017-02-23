#include "Dxlib.h"
#include "anime.h"

int AnimeLoop(int x, int y, int komasuu, int *handle, int oneframe, int *framemo, bool flag) {
	int modori = FALSE;
	if (*framemo == oneframe * komasuu) {
		modori = TRUE;
	}
	if (*framemo / oneframe > komasuu - 1) {
		*framemo = 0;
	}
	DrawGraph(x, y, handle[*framemo / oneframe], TRUE);
	if (flag) {
		(*framemo)++;
	}

	return modori;
	//
	
}
//
//戻り値がハンドルのバージョン
int AnimeLoop2(int komasuu, int *handle, int oneframe, int *framemo, bool flag) {
	bool modori = false;
	if (*framemo == oneframe * komasuu) {
		modori = true;
	}
	if (flag) {
		(*framemo)++;
	}

	if (*framemo / oneframe > komasuu - 1) {
		*framemo = 0;
	}
	return handle[*framemo / oneframe];
}

int AnimeFrame2(int komasuu, int *handle, int *oneframes, int *framemo, bool flag) {
	int finframe = 0, count;
	int fr1 = 0, fr2 = 0;
	int anscount = 0;
	bool graph_on = FALSE;
	for (count = 0; count < komasuu; count++) {
		finframe += oneframes[count];
	}
	int modori = FALSE;
	if (*framemo == finframe) {
		modori = TRUE;
	}
	if (*framemo > finframe) {
		*framemo = 0;
	}
	if (flag) {
		(*framemo)++;
	}
	if (*framemo >= 0 && *framemo <= oneframes[0]) {
		//DrawGraph(x, y, handle[0], TRUE);
		graph_on = TRUE;
	}
	else {
		for (count = 0; graph_on == FALSE; count++) {
			fr1 += oneframes[count];

			if (fr2 == 0) {
				fr2 += oneframes[count];
			}
			fr2 += oneframes[count + 1];

			if (*framemo >= fr1 && *framemo <= fr2) {
				//DrawGraph(x, y, handle[count + 1], TRUE);
				anscount = count + 1;
				graph_on = TRUE;
			}
		}
	}
	anscount = anscount % komasuu;
	return handle[anscount];
}

int AnimeFrame(int x, int y, int komasuu, int *handle, int *oneframes, int *framemo, bool flag) {
	int finframe = 0, count;
	int fr1 = 0, fr2 = 0;
	bool graph_on = FALSE;
	for (count = 0; count < komasuu; count++) {
		finframe += oneframes[count];
	}
	int modori = FALSE;
	if (*framemo == finframe) {
		modori = TRUE;
	}
	if (*framemo > finframe) {
		*framemo = 0;
	}

	if (*framemo >= 0 && *framemo <= oneframes[0]) {
		DrawGraph(x, y, handle[0], TRUE);
		graph_on = TRUE;
	}
	else {
		for (count = 0; graph_on == FALSE; count++) {
			fr1 += oneframes[count];

			if (fr2 == 0) {
				fr2 += oneframes[count];
			}
			fr2 += oneframes[count + 1];

			if (*framemo >= fr1 && *framemo <= fr2) {
				DrawGraph(x, y, handle[count + 1], TRUE);
				graph_on = TRUE;
			}
		}
	}
	if (flag) {
		(*framemo)++;
	}
	return modori;
}