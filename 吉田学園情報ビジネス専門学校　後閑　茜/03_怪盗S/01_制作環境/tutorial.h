//=============================================================================
//
// チュートリアル処理 [Tutorial.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TUTORIAL_H_ //二十インクルード防止のマクロ定義
#define _TUTORIAL_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_POS_X (0)												  //背景左上X
#define BG_POS_Y (0)												 //背景左上Y
#define TUTOTIAL_TEXTUER0 " "
#define TUTOTIAL_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial204.png"
#define TUTOTIAL_TEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png"
#define TUTOTIAL_TEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002-5.png"
#define MAX_TUTORIALTEX  (4)												   //テクスチャの枚数
#define MAX_ANIM (4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
#endif
