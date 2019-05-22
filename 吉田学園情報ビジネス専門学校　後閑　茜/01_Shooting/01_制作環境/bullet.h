//=============================================================================
//
// 弾処理 [bullet.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//列挙型
	BULLETTYPE_PLAYER = 0,//プレイヤーの弾
	BULLETTYPE_EMEMY,	 //敵の弾
	BULLET_MAX
}BULLETTYPE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,int Life);

#endif
