//=============================================================================
//
// 背景処理 [TitleRogo.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLEROGO_H_ //二十インクルード防止のマクロ定義
#define _TITLEROGO_

#include "main.h"
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
