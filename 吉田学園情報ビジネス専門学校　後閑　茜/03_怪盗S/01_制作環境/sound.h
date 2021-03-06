//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント(-1でループ再生)

} SOUNDPARAM;

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_SE_HIT,		// ヒット音0
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_PAUSE,		//ポーズ音
	SOUND_LABEL_SE_SELECT,		//ポーズセレクト
	SOUND_LABEL_SE_TUTORIALSELECT,		//チュートリアルセレクト
	SOUND_LABEL_SE_ITEMGET,		//チュートリアルセレクト
	SOUND_LABEL_SE_OAPNDOOR,		//チュートリアルセレクト
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
