//=============================================================================
//
// ポリゴン処理 [Bullet.h]
// Author : 後閑茜
//
//=============================================================================
#ifndef BULLET_H_
#define BULLET_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLET (128)		//弾の最大値
#define BULLET_POS_X (3.0f)		//弾のX
//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//回転
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 VecA;		//ベクトルA
	D3DXVECTOR3 VecC;		//ベクトルC
	int nIdxShadow;			//影の番号
	int nIdxEffect;			//エフェクトの番号
	bool bUse;				//使用状況

}Bullet;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Bullet*GetBullet(void);
#endif
