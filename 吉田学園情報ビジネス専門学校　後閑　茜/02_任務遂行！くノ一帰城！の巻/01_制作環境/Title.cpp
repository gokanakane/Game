//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include "TitleBG.h"
#include "TitleRogo.h"
#include"input.h"
#include"sound.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nTimeTitle;
//=============================================================================
// タイトル初期化処理[InitTitle]
//=============================================================================
void InitTitle(void)
{
	g_nTimeTitle = 0;
	InitTitleBG();
	InitTitleRogo();

}
//=============================================================================
//タイトル終了処理 [UninitTitle]
//=============================================================================
void UninitTitle(void)
{
	UninitTitleBG();
	UninitTitleRogo();
}

//=============================================================================
// タイトル更新処理[UpdataTitle]
//=============================================================================
void UpdateTitle(void)
{
	FADE g_Fade = GetFade();
	UpdateTitleBG();
	UpdateTitleRogo();
	g_nTimeTitle++;

	if (g_nTimeTitle > 600)
	{
		if (g_Fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_RANKING);
		}

	}

}
//=============================================================================
// タイトル描写処理[DrawTitle]
//=============================================================================
void DrawTitle(void)
{
	DrawTitleBG();
	DrawTitleRogo();
}