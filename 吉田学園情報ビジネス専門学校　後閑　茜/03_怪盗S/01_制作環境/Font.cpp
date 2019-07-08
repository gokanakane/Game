//=============================================================================
//
// 文字処理 [Font.h]
// Author : Gokan Akane
//
//=============================================================================
#include "Font.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXFONT g_pFont[MAX_LINE] = {};		//フォントへのポインタ
Font g_Font[MAX_LINE];

//*****************************************************************************
// 初期化処理
//*****************************************************************************
void InitFont(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		g_Font[nCnt].font[0] = {};
		g_Font[nCnt].bUse = false;

		//フォントの設定
		D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, //サイズ、X,Y,Z
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont[nCnt]);
	}
}
//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitFont(void)
{
	//フォントの開放
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_pFont[nCnt] != NULL)
		{
			g_pFont[nCnt]->Release();
			g_pFont[nCnt] = NULL;
		}
	}
}
//*****************************************************************************
// 更新処理
//*****************************************************************************
void UpdateFont(void) 
{

}
//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawFont(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//X座標、Y座標、X描画範囲、Y描画範囲

	//テキストの描画
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_Font[nCnt].bUse == true)
		{
			g_pFont[0]->DrawText(NULL, &g_Font[nCnt].font[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

}
//*****************************************************************************
// 文字の設定
//*****************************************************************************
void SetFont(char Font[256])
{
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_Font[nCnt].bUse == false)
		{
			wsprintf(&g_Font[nCnt].font[0], "%s", &Font[0]);
		
			g_Font[nCnt].bUse = true;
			break;
		}
	}
}
