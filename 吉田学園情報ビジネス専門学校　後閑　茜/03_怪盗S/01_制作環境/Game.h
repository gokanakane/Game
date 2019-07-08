//=============================================================================
//
// ゲーム処理 [Game.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0, //何もしていない
	GAMESTATE_NOMAL,	//通常
	GAMESTATE_CLEAR,
	GAMESTATE_OVER,
	GAMESTATE_MAX		//最大値

}GAMESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetPause(bool bPause);

#endif
