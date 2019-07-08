//=============================================================================
//
// 背景処理 [Result.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RESULT_H_ //二十インクルード防止のマクロ定義
#define _RESULT_

#include "main.h"
#include "Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEXTUER "data\\TEXTURE\\Result\\GameClear001.png"		//読み込むテクスチャ
#define RESULT_OVER "data\\TEXTURE\\Object\\Wall008.png"				//読み込むテクスチャ
#define RESULT_TEXTUER1 "data\\TEXTURE\\Result\\GameClear000.png"		//読み込むテクスチャ
#define RESULT_TEXTUER2 "data\\TEXTURE\\Result\\gameover000.png"		//読み込むテクスチャ
#define RESULT_CLIAR "data\\TEXTURE\\BG\\GameClear002.png"				//読み込むテクスチャ

#define RESULT_POS_X (0)												//リザルト左上X
#define RESULT_POS_Y (0)												//リザルト左上Y
#define RESULT_WIDTH (SCREEN_WIDTH)										//リザルトの幅
#define RESULT_HEIGHT (SCREEN_HEIGHT)									//リザルト高さ
#define MAX_OVER_TEX (2)												//テクスチャの最大数
#define MAX_CLIAR_TEX (3)												//ゲームクリアのテクスチャ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif
