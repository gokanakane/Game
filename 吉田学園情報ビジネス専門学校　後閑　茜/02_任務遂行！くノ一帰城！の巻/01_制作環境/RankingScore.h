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
// プロトタイプ宣言
//*****************************************************************************
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);

void SetHighScore(int nScore);

#endif
