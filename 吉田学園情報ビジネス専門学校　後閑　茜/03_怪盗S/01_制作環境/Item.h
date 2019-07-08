//=============================================================================
//
// アイテム処理 [Item.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef ITEM_H_
#define ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_TEXTURE1 "data\\TEXTURE\\Object\\Item001.png"
#define ITEM_TEXTURE2 "data\\TEXTURE\\Object\\Item002.png"
#define ITEM_TEXTURE3 "data\\TEXTURE\\Object\\Item003.png"
#define ITEM_TEXTURE4 "data\\TEXTURE\\Object\\Item004.png"
#define ITEM_TEXTURE5 "data\\TEXTURE\\Object\\Key004.png"

#define MAX_ITEMTEX (5)
#define MAX_ITEM (128)		//壁の最大値

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置z
	D3DXVECTOR3 rot;		//回転
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int IdxShadow;			//影番号
	int IdxItem;			//アイテム番号
	int Type;
	bool bUse;				//使用状況
}Item;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

Item *GetItem(void);
void SetItem(D3DXVECTOR3 pos,int Type);
void DeleteItem(int nType);
#endif
