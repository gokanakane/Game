//=============================================================================
//
// ポーズ処理 [Pause.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSE_H_ //二十インクルード防止のマクロ定義
#define _PAUSE_H_

#include "main.h"

typedef enum
{
	PAUSESTATE_NONE = 0,
	PAUSESTATE_CONTINUE,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX

} PAUSESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif
