//=============================================================================
//
// ビルボード処理 [Billboard.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BILLBOARD (128)		//壁の最大値
#define MAX_TEX (4)

#define KEY_TEXTUER "data\\TEXTURE\\Key000.png"
#define KEY_TEXTUER1 "data\\TEXTURE\\Key001.png"
#define KEY_TEXTUER2 "data\\TEXTURE\\Key002.png"
#define KEY_TEXTUER3 "data\\TEXTURE\\Key003.png"

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置z
	D3DXVECTOR3 rot;		//回転
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int IdxShadow;			//影番号
	int Type;
	bool bUse;				//使用状況
}Billboard;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

void SetBillboard(D3DXVECTOR3 pos,int Type);
#endif
