//=============================================================================
//
// 背景処理 [PauseRetry.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSERETRY_H_ //二十インクルード防止のマクロ定義
#define _PAUSERETRY_

#include "main.h"

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
