//=============================================================================
//
// 敵弓処理 [Bow.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _BOW_H_
#define _BOW_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BOW		(120)		// 弾の最大数
#define BOW_TEXTUER "data\\TEXTURE\\Object\\bow.png"
#define BOW_TEXTUER1 "data\\TEXTURE\\Object\\bow001.png"

#define POS_Y (620)
#define BOW_MOVE (1.0f)
#define BOW_PATTERN		(5)
#define MAX_BOW_TYPE (2)
#define MAX_TEX (2)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	int type;
	int nLife;//弓の寿命
	bool bUse;//使っているかどうか

}Bow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBow(void);
void UninitBow(void);
void UpdateBow(void);
void DrawBow(void);
void SetBow(D3DXVECTOR3 pos, D3DXVECTOR3 move,int type);

Bow*GetBow(void);
#endif
