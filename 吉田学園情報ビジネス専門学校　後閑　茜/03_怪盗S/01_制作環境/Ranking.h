//=============================================================================
//
// 背景処理 [Ranking.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RANKING_H_ //二十インクルード防止のマクロ定義
#define _RANKING_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_TEXTURE "data\\TEXTURE\\Ranking\\Ranking000.png"	//ランキング文字
#define RANKING_TEXTURE0 "　"										//背景
#define RANKING_TEXTURE1 "data\\TEXTURE\\BG\\Dot.png"				//ドット（スクロール）
#define RANKING_TEXTURE2 "data\\TEXTURE\\Ranking\\Ranking001.png"	//順位
#define RANKING_TEXTURE3 "data\\TEXTURE\\Ranking\\Ranking002.png"	//怪盗
#define RANKING_TEXTURE4 "data\\TEXTURE\\Ranking\\Ranking003.png"	//ペンダント（アニメーション）
#define Ranking_POS_X (300)											//タイトル左上X
#define Ranking_POS_Y (500)											//タイトル左上Y
#define Ranking_WIDTH (SCREEN_WIDTH)								//タイトルの幅
#define Ranking_HEIGHT (SCREEN_HEIGHT)								//タイトル高さ
#define MAX_RANKINGTEX (6)
#define MAX_ANIM (4)												//アニメーションパターン

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
#endif
