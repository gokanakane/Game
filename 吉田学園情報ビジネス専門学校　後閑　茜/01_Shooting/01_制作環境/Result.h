//=============================================================================
//
// リザルト処理 [Result.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RESULT_H_ //二十インクルード防止のマクロ定義
#define _RESULT_H_

#include "main.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEXTUER "data\\TEXTURE\\BG\\Bg111.jpg" //読み込むテクスチャ
#define RESULT_OVER "data\\TEXTURE\\BG\\Bg110.png" //読み込むテクスチャ
#define RESULT_TEXTUER1 "data\\TEXTURE\\UI\\gameclear_logo.png" //読み込むテクスチャ
#define RESULT_TEXTUER2 "data\\TEXTURE\\UI\\gameover_logo.png" //読み込むテクスチャ
#define RESULT_POS_X (0)					   //リザルト左上X
#define RESULT_POS_Y (0)					   //リザルト左上Y
#define RESULT_WIDTH (SCREEN_WIDTH)			   //リザルトの幅
#define RESULT_HEIGHT (SCREEN_HEIGHT)		   //リザルト高さ
#define MAX_RESULTTEX (2)							   //テクスチャの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif
