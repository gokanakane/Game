//=============================================================================
//
// ランキングスコア処理 [RankingScore.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RANKINGSCORE "data\\TEXTURE\\UI\\number000.png"	// 読み込むテクスチャファイル名
#define MAX_RANKINGSCORE (8)							    //スコアの桁数
#define MAX_RANKINGSCORE_HEIGTH (5)							//スコアの段数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);

void SetHighScore(int nScore);

#endif
