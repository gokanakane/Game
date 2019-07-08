//=============================================================================
//
// タイトルロゴ処理 [TitleRogo.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TITLEROGO_H_ //二十インクルード防止のマクロ定義
#define _TITLEROGO_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLEROGO_TEXTUER "data\\TEXTURE\\Title\\TitleBG1.png" //読み込むテクスチャ
#define TITLEROGO_TEXTUER1 "data\\TEXTURE\\Title\\Title001.png" //読み込むテクスチャ
#define TITLEROGO_TEXTUER2 "data\\TEXTURE\\UI\\PRESS_ENTER.png" //読み込むテクスチャ
#define TITLEROGO_TEXTUER3 "data\\TEXTURE\\Title\\Title002.png" //読み込むテクスチャ

#define TITLEROGO_POS_X (300)					   //タイトル左上X
#define TITLEROGO_POS_Y (500)					   //タイトル左上Y
#define TITLEROGO_WIDTH (SCREEN_WIDTH)			   //タイトルの幅
#define TITLEROGO_HEIGHT (SCREEN_HEIGHT)		   //タイトル高さ
#define MAX_TITLEROGOTEX (4)
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
	int nCntAnim;	//アニメーションカウンター
	int nPatturnAnim;//アニメーションパターン
	float nChangeArpha;//透明度変更
	bool bAnim;

}RogoAnim;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitleRogo(void);
void UninitTitleRogo(void);
void UpdateTitleRogo(void);
void DrawTitleRogo(void);

RogoState*GetState(void);
#endif
