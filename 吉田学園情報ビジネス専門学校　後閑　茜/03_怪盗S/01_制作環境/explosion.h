//=============================================================================
//
// ポリゴン処理 [Explosion.h]
// Author : 後閑茜
//
//=============================================================================
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_EXPLOSION (128)		//壁の最大値
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置z
	D3DXVECTOR3 rot;		//回転
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nPatturnAnim;		//アニメーションパターン
	int nCntAnim;			//アニメーションカウンター
	bool bUse;				//使用状況
}Explosion;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplosion(D3DXVECTOR3 pos);
#endif
