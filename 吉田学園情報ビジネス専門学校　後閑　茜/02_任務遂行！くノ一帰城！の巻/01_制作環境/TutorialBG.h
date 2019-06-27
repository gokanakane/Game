//=============================================================================
//
// 背景処理 [TutorialBG.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TUTORIALBG_H_ //二十インクルード防止のマクロ定義
#define _TUTORIALBG_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_POS_X (0)					   //背景左上X
#define BG_POS_Y (300)					   //背景左上Y
#define MAX_TUTORIALBGTEX  (4)					   //テクスチャの枚数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	TUTORIALSTATE_NONE = 0,
	TUTORIALSTATE_FADEIN,
	TUTORIALSTATE_FADEOUT,
	TUTORIALTATE_MAX

}TutorialState;
typedef struct
{
	D3DXCOLOR col;
	float nChangeArpha;//透明度変更

}TutorialCol;


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TUTOTIALTEXTUER  "data\\TEXTURE\\Tutorial\\Tutorial003.png" //読み込むテクスチャ
#define BG_TUTOTIALTEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png" //読み込むテクスチャ
#define BG_TUTOTIALTEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002.png" //読み込むテクスチャ
#define BG_TUTOTIALTEXTUER3 "data\\TEXTURE\\Tutorial\\Tutorial004.png" //読み込むテクスチャ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTutorialBG(void);
void UninitTutorialBG(void);
void UpdateTutorialBG(void);
void DrawTutorialBG(void);
#endif
