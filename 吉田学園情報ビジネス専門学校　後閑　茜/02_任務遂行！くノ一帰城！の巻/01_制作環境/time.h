//=============================================================================
//
// タイム処理 [Time.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_

#include "main.h"

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef enum
{
	TIMESTATE_NONE=0,
	TIMESTATE_NOMAL,
	TIMESTATE_END,
	TIMESTATE_MAX

}TIMESTATE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void AddTime(void);

void SetTimeState(TIMESTATE state);
int GetTime(void);
#endif
