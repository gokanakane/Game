//=============================================================================
//
// 影処理 [Shadow.h]
// Author : 後閑茜
//
//=============================================================================
#ifndef _SHADOW_H__
#define _SHADOW_H__

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SHADOW (128)	//影の最大数
#define SHADOW_TEXTUER "data\\TEXTURE\\Effect\\shadow000.jpg"

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転
	D3DXCOLOR col;				//色
	D3DXMATRIX g_mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用状況

}Shadow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int IdxShadow, D3DXVECTOR3 pos);
void DeleteShadow(int nIdxShadow);
#endif
