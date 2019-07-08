//=============================================================================
//
// アイテム取得UI処理 [ItemGet.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ITEMGET_H_
#define _ITEMGET_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ITEMGET "data\\TEXTURE\\Object\\Item001.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET1 "data\\TEXTURE\\Object\\Item002.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET2 "data\\TEXTURE\\Object\\Item003.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET3 "data\\TEXTURE\\Object\\Item004.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ITEMGET4 "data\\TEXTURE\\Object\\Key004.png"	// 読み込むテクスチャファイル名
#define MAX_ITEMGETTEX (5)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	bool bUse;
	int nType;
	int nIdxItem;
}ItemUI;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItemGetUI(void);
void UninitItemGetUI(void);
void UpdateItemGetUI(void);
void DrawItemGetUI(void);

ItemUI*GetItemUI(void);
int SetItemGetUI(int nType);
void DeleteItemGetUI(int nType);
#endif
