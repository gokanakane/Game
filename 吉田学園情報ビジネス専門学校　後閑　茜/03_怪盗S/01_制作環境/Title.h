//=============================================================================
//
// 背景処理 [Title.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TITLE_H_ //二十インクルード防止のマクロ定義
#define _TITLE_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLEROGO_TEXTUER "data\\TEXTURE\\UI\\Title000.png"			//読み込むテクスチャ
#define TITLEROGO_TEXTUER1 "data\\TEXTURE\\UI\\PRESS_ENTER.png"		//読み込むテクスチャ
#define TITLEROGO_POS_X (300)										//タイトル左上X
#define TITLEROGO_POS_Y (500)										//タイトル左上Y
#define TITLEROGO_WIDTH (SCREEN_WIDTH)								//タイトルの幅
#define TITLEROGO_HEIGHT (SCREEN_HEIGHT)							//タイトル高さ
#define MAX_TEX (2)
#define MAX_ANIMATION (4)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef enum
{
	ROGO_NONE = 0,		// 何もしていない状態
	ROGO_FLASH,			// ENTER入力状態
	ROGO_MAX
} RogoState;

typedef struct
{
	D3DXCOLOR col;
	float nChangeArpha;//透明度変更
	bool bAnim;

}RogoAnim;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
