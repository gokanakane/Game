//=============================================================================
//
// 背景処理 [Title_Select.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLE_SELECTH_ //二十インクルード防止のマクロ定義
#define _TITLE_SELECT

#include "main.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLESELECT_TEXTUER  "data\\TEXTURE\\UI\\GAMESTART.png"		//読み込むテクスチャ
#define TITLESELECT_TEXTUER1  "data\\TEXTURE\\UI\\Tutorial100.png"	//読み込むテクスチャ
#define TITLESELECT_TEXTUER2  "data\\TEXTURE\\UI\\cursor.png"			//読み込むテクスチャ

#define MAX_TEX (2)
#define TITLESELECT_POS_X (320)												//ポーズ文字（YES）左上X
#define TITLESELECT_POS_Y (300)												//ポーズ文字（YES）左上Y
#define TITLESELECT_WIDTH (990)												//ポーズ文字（YES）の幅
#define TITLESELECT_HEIGHT (500)												//ポーズ文字（YES）高さ

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
