//=============================================================================
//
// モデル処理 [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMYMODEL (2)			//モデルの数
#define MAX_ENEMY (128)				//敵の最大数
//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMesh;			//メッシュ情報（頂点情報）のポインタ
	LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
	DWORD NumMat;				//マテリアル情報の数
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転

}EnemyModel;

typedef struct
{
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 rot;			//回転
	D3DXVECTOR3 move;			//移動量
	D3DXCOLOR col;				//色
	D3DXVECTOR3 vtxMin;			//モデルの最小値
	D3DXVECTOR3 vtxMax;			//モデルの最大値
	D3DXVECTOR3 VecA;		//ベクトルA
	D3DXVECTOR3 VecC;		//ベクトルC
	int nIdxShadow;				//影番号
	float nCntMove;				//移動カウンター
	float nChengeMove;			//移動量
	int nType;					//0:横移動　1:縦移動
	bool bUse;					//使用状況
	EnemyModel aModel;	//[　]＝モデルの数
}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

Enemy*GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ChengeMove, int Type);
void CollisionStageEN(void);
bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
#endif
