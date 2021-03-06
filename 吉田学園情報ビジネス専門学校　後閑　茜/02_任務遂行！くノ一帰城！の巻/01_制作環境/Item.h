//=============================================================================
//
// アイテム処理 [Item.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM		(128)		// 弾の最大数
#define ITEM_TEXTUER "data\\TEXTURE\\Object\\Item000.png"
#define ITEM_TEXTUER1 "data\\TEXTURE\\Object\\Item001.png"
#define ITEM_TEXTUER2 "data\\TEXTURE\\Object\\Item002.png"
#define ITEM_TEXTUER3 "data\\TEXTURE\\Object\\makimono.png"

#define COIN_PATTERN (4)
#define ITEM_MOVE (3.0f)
#define MAX_ITEMTEX (4)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//typedef enum
//{//列挙型
//	ITEMTYPE_COIN = 0,//コイン
//	ITEMTYPE_MAX
//
//}ITEMTYPE;

typedef struct 
{
	D3DXVECTOR3 pos; //位置 
	D3DXVECTOR3 move;//移動量
	D3DXCOLOR col;	 //色
	int nCntAnim;	 //アニメーションカウンター
	int nPatternAnim;//パターンNo
	int nType;		//アイテムのタイプ
	bool bUse;		 //使っているかどうか

}ITEM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos,int Type);

bool CollsionItem(D3DXVECTOR3 *pPos);
void DeleteItem(int nCnt);
ITEM*GetItem(void);
#endif
