//=============================================================================
//
// スコア処理 [ItemGet.h]
// Author : Gokan akane
//
//=============================================================================
#ifndef _ITEMGET_H_
#define _ITEMGET_H_

#include "main.h"
#include "Game.h"

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
