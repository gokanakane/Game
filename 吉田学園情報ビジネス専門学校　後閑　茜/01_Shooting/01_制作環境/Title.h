//=============================================================================
//
// タイトル処理 [Title.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TITLE_H_ //二十インクルード防止のマクロ定義
#define _TITLE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTUER "data\\TEXTURE\\BG\\BG01.png" //読み込むテクスチャ
#define TITLE_TEXTUER1 "data\\TEXTURE\\UI\\press_enter.png" //読み込むテクスチャ
#define TITLE_TEXTUER2 "data\\TEXTURE\\UI\\Title.png" //読み込むテクスチャ
#define TITLE_POS_X (0)					   //タイトル左上X
#define TITLE_POS_Y (0)					   //タイトル左上Y
#define TITLE_WIDTH (SCREEN_WIDTH)			   //タイトルの幅
#define TITLE_HEIGHT (SCREEN_HEIGHT)		   //タイトル高さ
#define MAX_TITLETEX (3)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
