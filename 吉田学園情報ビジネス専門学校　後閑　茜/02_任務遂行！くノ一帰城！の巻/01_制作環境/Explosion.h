//=============================================================================
//
// 爆発処理 [Explosion.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _EXPLOSON_H_
#define _EXPLOSION_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// 爆発の最大数
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"
#define MAX_PATTERN (3)

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
