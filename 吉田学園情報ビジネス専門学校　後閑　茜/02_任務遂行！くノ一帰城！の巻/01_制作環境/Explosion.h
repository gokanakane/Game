//=============================================================================
//
// 弾処理 [Explosion.h]
// Author :
//
//=============================================================================
#ifndef _EXPLOSON_H_
#define _EXPLOSION_H_

#include "main.h"
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //位置 
	D3DXVECTOR3 move; //位置 
	D3DXCOLOR col;	 //色
	int nCntAnim;	 //アニメーションカウンター
	int nPatternAnim;//パターンNo
	bool bUse;		 //使っているかどうか

}Explosion;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

Explosion*GetExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif
