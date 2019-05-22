//=============================================================================
//
// 背景処理 [PauseQuit.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSEQUIT_H_ //二十インクルード防止のマクロ定義
#define _PAUSEQUIT_

#include "main.h"

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