//=============================================================================
//
// 背景処理 [PauseContinue.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSECONRINUE_H_ //二十インクルード防止のマクロ定義
#define _PAUSECONRINUE_

#include "main.h"

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
