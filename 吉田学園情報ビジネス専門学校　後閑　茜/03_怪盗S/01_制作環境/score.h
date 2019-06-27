//=============================================================================
//
// スコア処理 [score.h]
// Author : Gokan akane
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data\\TEXTURE\\UI\\number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_SCORE1		"data\\TEXTURE\\UI\\Score000.png"	// 読み込むテクスチャファイル名
#define MAX_SCORE (8)
#define MAX_SCORETEX (2)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue);
int GetScore(void);
#endif
