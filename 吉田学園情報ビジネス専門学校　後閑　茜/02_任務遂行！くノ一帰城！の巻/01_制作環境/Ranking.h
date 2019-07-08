//=============================================================================
//
// ランキング処理 [Ranking.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RANKING_H_ //二十インクルード防止のマクロ定義
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_TEXTURE "data\\TEXTURE\\UI\\Ranking000.png" //ランキング文字
#define RANKING_TEXTURE0 "data\\TEXTURE\\BG\\Sky001.jpg"	//背景
#define RANKING_TEXTURE2 "data\\TEXTURE\\UI\\Ranking001.png"//順位
#define Ranking_POS_X (300)									//タイトル左上X
#define Ranking_POS_Y (500)									//タイトル左上Y
#define Ranking_WIDTH (SCREEN_WIDTH)						//タイトルの幅
#define Ranking_HEIGHT (SCREEN_HEIGHT)						//タイトル高さ
#define MAX_TEX (3)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
#endif
