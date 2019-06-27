//=============================================================================
//
// 背景処理 [TUTORIAL.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TUTORIAL_H_ //二十インクルード防止のマクロ定義
#define _TUTORIAL_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIAL_TEXTUER1 "data\\TEXTURE\\UI\\tutorial000.png" //読み込むテクスチャ
#define TUTORIAL_POS_X (0)					   //背景左上X
#define TUTORIAL_POS_Y (0)					   //背景左上Y
#define TUTORIAL_WIDTH (SCREEN_WIDTH)			   //背景の幅
#define TUTORIAL_HEIGHT (SCREEN_HEIGHT)		   //背景高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
#endif
