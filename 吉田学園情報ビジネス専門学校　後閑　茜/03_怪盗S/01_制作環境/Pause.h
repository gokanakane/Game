//=============================================================================
//
// 背景処理 [Pause.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSE_H_ //二十インクルード防止のマクロ定義
#define _PAUSE_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	PAUSESTATE_NONE = 0,
	PAUSESTATE_CONTINUE,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX
} PAUSESTATE;
typedef enum
{
	PAUSESTATECOLOR_NONE = 0,
	PAUSESTATECOLOR_CONTINUE,
	PAUSESTATECOLOR_RETRY, 
	PAUSESTATECOLOR_QUIT,
	CONTINUSTATE_MAX

} COLORSTATE;

typedef struct
{
	bool bAnim;			//アニメーション状況
	D3DXVECTOR3 pos;	//位置
	float CntMove;		//移動量のカウンター
	float ChengeMove;	//移動量
	int CntAnim;		//アニメーションカウンター
	int PatturnAnim;	//アニメーションパターン

}Pause;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif
