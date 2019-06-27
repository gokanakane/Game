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
// マクロ定義
//*****************************************************************************
#define MAX_TEX (5)													 //テクスチャの数
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Pause\\Continue.png"	//読み込むテクスチャ
#define PAUSERETRY_TEXTUER  "data\\TEXTURE\\Pause\\Retry.png"		//読み込むテクスチャ
#define PAUSEQUIT_TEXTUER  "data\\TEXTURE\\Pause\\Quit.png"			//読み込むテクスチャ
#define PAUSE_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial001.png"	//読み込むテクスチャ
#define PAUSEMASK_TEXTURE " "
#define PAUSEBG_POS_X (630)											//ポーズ背景左上X
#define PAUSEBG_POS_Y (180)											//ポーズ背景左上Y
#define PAUSEBG_WIDTH (990)											//ポーズ背景の幅
#define PAUSEBG_HEIGHT (580)										//ポーズ背景高さ
#define PASUSE_WIDTH (110.0f)										//ロゴの間隔
#define MAX_MENU (3)												//選択肢の数
#define MAX_ANIMATION (4)											//アニメーションパターン

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
