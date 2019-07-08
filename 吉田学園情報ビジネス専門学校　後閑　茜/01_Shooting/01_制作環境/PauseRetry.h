//=============================================================================
//
// リトライアイコン処理 [PauseRetry.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSERETRY_H_ //二十インクルード防止のマクロ定義
#define _PAUSERETRY_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSERETRY_TEXTUER  "data\\TEXTURE\\Pause\\pause001.png" //読み込むテクスチャ
#define PAUSERETRY_POS_X (280 + 150)					    //ポーズ背景左上X
#define PAUSERETRY_POS_Y (280 - 80)					    //ポーズ背景左上Y
#define PAUSERETRY_WIDTH (640 + 150)					    //ポーズ背景の幅
#define PAUSERETRY_HEIGHT (640 - 80)					    //ポーズ背景高さ

//*****************************************************************************
// リトライの状態
//*****************************************************************************
typedef enum
{
	RETRYSTATE_SELECT = 0,
	RETRYSTATE_NOSELECT,
	RETRYSTATE_MAX

} RETRYSTATE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPauseRetry(void);
void UninitPauseRetry(void);
void UpdatePauseRetry(void);
void DrawPauseRetry(void);

void SetRetry(RETRYSTATE state);
#endif
