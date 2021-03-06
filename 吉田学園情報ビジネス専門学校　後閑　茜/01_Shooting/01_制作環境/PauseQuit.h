//=============================================================================
//
// クイットアイコン処理 [PauseQuit.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSEQUIT_H_ //二十インクルード防止のマクロ定義
#define _PAUSEQUIT_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSEQUIT_TEXTUER  "data\\TEXTURE\\Pause\\pause002.png" //読み込むテクスチャ
#define PAUSEQUIT_POS_X (280 + 150)					    //ポーズ背景左上X
#define PAUSEQUIT_POS_Y (280 - 80)					    //ポーズ背景左上Y
#define PAUSEQUIT_WIDTH (640 + 150)					    //ポーズ背景の幅
#define PAUSEQUIT_HEIGHT (640 - 80)					    //ポーズ背景高さ

//*****************************************************************************
// クイットの状態
//*****************************************************************************
typedef enum
{
	QUITSTATE_SELECT = 0,
	QUITSTATE_NOSELECT,
	QUITSTATE_MAX

} QUITSTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPauseQuit(void);
void UninitPauseQuit(void);
void UpdatePauseQuit(void);
void DrawPauseQuit(void);

void SetQuit(QUITSTATE state);

#endif