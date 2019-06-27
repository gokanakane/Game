//=============================================================================
//
// 背景処理 [bg.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _BG_H_ //二十インクルード防止のマクロ定義
#define _BG_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TEXTUER  "data\\TEXTURE\\BG\\sky001.jpg" //読み込むテクスチャ
#define BG_TEXTUER1 "data\\TEXTURE\\BG\\cloud.png" //読み込むテクスチャ
#define BG_TEXTUER2 "data\\TEXTURE\\BG\\BG000.png" //読み込むテクスチャ
#define BG_POS_X (0)					   //背景左上X
#define BG_POS_Y (300)					   //背景左上Y
#define BG_WIDTH (SCREEN_WIDTH)			   //背景の幅
#define BG_HEIGHT (SCREEN_HEIGHT)		   //背景高さ
#define MAX_TEX  (3)					   //テクスチャの枚数
#define BG_MOVE (3.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
#endif
