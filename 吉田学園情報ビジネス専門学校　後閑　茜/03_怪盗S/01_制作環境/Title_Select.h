//=============================================================================
//
// 背景処理 [Select_Yes.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLE_SELECTH_ //二十インクルード防止のマクロ定義
#define _TITLE_SELECT

#include "main.h"
#include "Game.h"

typedef enum
{
	COLSTATE_GAMESTATE = 0,
	COLSTATE_TUTORIAL,
	COLSTATE_MAX

}Colstate;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitleSelect(void);
void UninitTitleSelect(void);
void UpdateTitleSelect(void);
void DrawTitleSelect(void);

#endif
