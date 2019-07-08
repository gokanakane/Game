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
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME "data\\TEXTURE\\UI\\number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_TIME2 "data\\TEXTURE\\UI\\Clock000.png"	// 読み込むテクスチャファイル名
#define MAX_TIME (3)
#define TIME_RIMIT (60*90)							//制限時間
#define MAX_TIMETEX (2)									//テクスチャの最大数

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
