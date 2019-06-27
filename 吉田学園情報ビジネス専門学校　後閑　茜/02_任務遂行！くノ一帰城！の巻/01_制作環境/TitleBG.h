//=============================================================================
//
// 背景処理 [TitleBG.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLEBG_H_ //二十インクルード防止のマクロ定義
#define _TITLEBG_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLEBG_TEXTUER "data\\TEXTURE\\BG\\TitleBG00.png" //読み込むテクスチャ
#define TITLEBG_TEXTUER1 "data\\TEXTURE\\Title\\TitlePC.png" //読み込むテクスチャ

#define TITLEBG_POS_X (0)						//タイトル左上X
#define TITLEBG_POS_Y (0)						//タイトル左上Y
#define TITLEBG_WIDTH (SCREEN_WIDTH)			//タイトルの幅
#define TITLEBG_HEIGHT (SCREEN_HEIGHT)			//タイトル高さ
#define MAX_TEX (2)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXCOLOR col;
	int nCntAnim;	//アニメーションカウンター
	int PatternAnim;//アニメーションパターン

}BGAnim;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitleBG(void);
void UninitTitleBG(void);
void UpdateTitleBG(void);
void DrawTitleBG(void);

#endif
