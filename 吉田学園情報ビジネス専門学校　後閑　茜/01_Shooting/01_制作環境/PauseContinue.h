//=============================================================================
//
// コンテニューアイコン処理 [PauseContinue.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSECONRINUE_H_ //二十インクルード防止のマクロ定義
#define _PAUSECONRINUE_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Pause\\pause000.png" //読み込むテクスチャ
#define PAUSE_POS_X (280 + 150)					    //ポーズ背景左上X
#define PAUSE_POS_Y (280 - 80)					    //ポーズ背景左上Y
#define PAUSE_WIDTH (640 + 150)					    //ポーズ背景の幅
#define PAUSE_HEIGHT (640 - 80)					    //ポーズ背景高さ

//*****************************************************************************
// コンテニューの状態
//*****************************************************************************
typedef enum
{
	CONTINUSTATE_SELECT = 0,
	CONTINUSTATE_NOSELECT,
	CONTINUSTATE_MAX

} CONTINUSTATE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPauseContinue(void);
void UninitPauseContinue(void);
void UpdatePauseContinue(void);
void DrawPauseContinue(void);

void SetContinu(CONTINUSTATE state);

#endif
