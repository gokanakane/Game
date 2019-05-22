//=============================================================================
//
// モデル処理 [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYERMODEL (15)			//モデルの数

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
	int nIdxModel;				//モデルのインデックス

}PlayerModel;

typedef struct
{
	LPD3DXMESH pMesh;			//メッシュ情報（頂点情報）のポインタ
	LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
	DWORD NumMat;				//マテリアル情報の数
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 rot;			//回転
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 VecA;		//ベクトルA
	D3DXVECTOR3 VecC;		//ベクトルC
	D3DXCOLOR col;				//色
	D3DXVECTOR3 vtxMin;			//モデルの最小値
	D3DXVECTOR3 vtxMax;			//モデルの最大値
	int nIdxShadow;				//影番号
	PlayerModel aModel[MAX_PLAYERMODEL];	//[　]＝モデルの数
}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player*GetPlayer(void);
void CollisionStagePL(void);

#endif
